import path from 'path';
import {createServer} from "http";
import {Server as HttpServer} from "node-static";
import {WebSocketServer} from "ws";
import {fileURLToPath} from 'url';

let wsBrowserClient;
let wsEditorClient;

const __filename = fileURLToPath(import.meta.url);

const __dirname = path.dirname(__filename);

const PORT = 8080;

const httpServer = new HttpServer(`${__dirname}/../Client`);

console.log(`port: ${PORT}`);

const server = createServer((req, res) => {
    req.addListener("end", () => {
        httpServer.serve(req, res);
    }).resume();
});

const wsServer = new WebSocketServer({server});

const messageType = {
    auth: "auth",
    seekTimeline: "seekTimeline",
    exportScene: "exportScene"
}

const clientType = {
    browser: "browser",
    editor: "editor",
}

const auth = (ws, json) => {
    // is browser
    if (!json.clientType) {
        console.error(`auth: hasnot client type - ${json.clientType}`)
        return;
    }

    switch (json.clientType) {
        case clientType.browser:
            console.log("connect with browser");
            wsBrowserClient = ws;
            break;
        case clientType.editor:
            console.log("connect with editor");
            wsEditorClient = ws;
            break;
        default:
            console.error(`auth: invalid client type - ${json.clientType}`)
            break;
    }
}

const seekTimeline = (json) => {
    if (!wsBrowserClient) {
        return;
    }
    // console.log(json);
    const newData = {
        type: messageType.seekTimeline,
        currentTime: json.currentTime
    };
    console.log(`send to browser data: ${newData}`);
    wsBrowserClient.send(JSON.stringify(newData))
}

const exportScene = (json) => {
    if (!wsBrowserClient) {
        return;
    }
    // console.log(json);
    const newData = {
        type: messageType.exportScene,
    };
    console.log(`send to browser data: ${newData}`);
    wsBrowserClient.send(JSON.stringify(newData))
}

wsServer.on("connection", (ws) => {
    console.log("server: connected")
    ws.send("server -> client: connected");

    ws.on("error", (e) => {
        console.error(e);
    });

    ws.on("close", (code, reason) => {
        console.log(`close - code: ${code}, reason: ${reason}`);
        if (wsBrowserClient === ws) {
            console.log("disconnect with browser")
            wsBrowserClient = null;
        }
    });

    ws.on("message", (data) => {
        console.log("received");
        console.log(data.toString());

        const json = JSON.parse(data.toString());

        if (!json.type) {
            return;
        }

        switch (json.type) {
            case messageType.auth:
                auth(ws, json);
                break;
            case messageType.seekTimeline:
                seekTimeline(json);
                break;
            case messageType.exportScene:
                exportScene(json);
                break;
            default:
                console.error(`invalid message type: ${json.type}`);
        }
    });
});

server.on("listening", () => {
    console.log("on listen.");
});
server.listen(PORT);
