// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebSocketConnector.generated.h"

class IWebSocket;

DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketConnector, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSockMsg, FString, message);

UCLASS()
class MARIONETTER_API AWebSocketConnector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWebSocketConnector();

	UFUNCTION(BlueprintCallable, Category="WebSocketConnector")
	virtual void Connect();

	UFUNCTION(BlueprintCallable, Category="WebSocketConnector")
	virtual void Disconnect();
	
	UFUNCTION(BlueprintCallable, Category="WebSocketConnector")
	virtual void SendMessage(const FString& message);

	UFUNCTION(BlueprintPure, Category="WebSocketConnector")
	FString CurrentMessage() const;

	UPROPERTY(BlueprintAssignable, Category="WebSocketConnector")
	FSockMsg OnReceiveSocketMessage;

	// UPROPERTY(BlueprintReadWrite, Category="Core")
	// FString url;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnConnected() const;
	void OnConnectionError(const FString& err) const;
	void OnSocketClosed(const int statusCode, const FString& reason, const bool isClean) const;
	void OnSocketMessageReceived(const FString& message);

	TSharedPtr<IWebSocket> Socket = nullptr;
	FString currentMessage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
