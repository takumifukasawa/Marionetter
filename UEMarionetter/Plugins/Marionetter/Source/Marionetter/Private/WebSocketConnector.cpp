
// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocketConnector.h"

#include "IWebSocket.h"
#include "WebSocketsModule.h"

DEFINE_LOG_CATEGORY(LogWebSocketConnector)

// Sets default values
AWebSocketConnector::AWebSocketConnector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWebSocketConnector::BeginPlay()
{
	Super::BeginPlay();
}

void AWebSocketConnector::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AWebSocketConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWebSocketConnector::Connect()
{
	UE_LOG(LogWebSocketConnector, Log, TEXT("Initialize"));
	const FString url = TEXT("ws://localhost:8080");
	const FString protocol = TEXT("ws");

	Socket = FWebSocketsModule::Get().CreateWebSocket(url, protocol);
	UE_LOG(LogWebSocketConnector, Log, TEXT("Open Socket"));

	if (Socket == nullptr)
	{
		UE_LOG(LogWebSocketConnector, Error, TEXT("Connect: Invalid Socket"));
		return;
	}

	Socket->OnConnected().AddUObject(this, &AWebSocketConnector::OnConnected);
	Socket->OnConnectionError().AddUObject(this, &AWebSocketConnector::OnConnectionError);
	Socket->OnClosed().AddUObject(this, &AWebSocketConnector::OnSocketClosed);
	Socket->OnMessage().AddUObject(this, &AWebSocketConnector::OnSocketMessageReceived);

	Socket->Connect();
}

void AWebSocketConnector::Disconnect()
{
	UE_LOG(LogWebSocketConnector, Log, TEXT("Dispose"));
	if (Socket != nullptr)
	{
		Socket->Close();
		UE_LOG(LogWebSocketConnector, Log, TEXT("Close Socket"));
	}
	Socket = nullptr;
}

void AWebSocketConnector::SendMessage(const FString& message)
{
	// for debug
	// UE_LOG(LogWebSocketConnector, Log, TEXT("SendMessage: %s"), *message);
	if (Socket == nullptr)
	{
		UE_LOG(LogWebSocketConnector, Error, TEXT("SendMessage: Invalid Socket"));
		return;
	}
	Socket->Send(message);
}

FString AWebSocketConnector::CurrentMessage() const
{
	return currentMessage;
}

void AWebSocketConnector::OnConnected() const
{
	UE_LOG(LogWebSocketConnector, Log, TEXT("OnConnected"));
}

void AWebSocketConnector::OnConnectionError(const FString& err) const
{
	UE_LOG(LogWebSocketConnector, Log, TEXT("OnConnectionError: %s"), *err);
}

void AWebSocketConnector::OnSocketClosed(const int statusCode, const FString& reason, const bool isClean) const
{
	UE_LOG(
		LogWebSocketConnector,
		Log,
		TEXT("OnSocketClosed: %d, %s, %ls"),
		statusCode,
		*reason,
		(isClean ? TEXT("true") : TEXT("false"))
	);
}

void AWebSocketConnector::OnSocketMessageReceived(const FString& message)
{
	UE_LOG(LogWebSocketConnector, Log, TEXT("OnSocketMesssageReceived: %s"), *message);
	currentMessage = message;
	OnReceiveSocketMessage.Broadcast(currentMessage);
}
