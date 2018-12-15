// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DebugDraw2dSampleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGDRAW2DSAMPLE_API ADebugDraw2dSampleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	ADebugDraw2dSampleGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:
	void Draw(UCanvas* InCanvas, APlayerController* PC);

private:
	FDelegateHandle			DrawDebugDelegateHandle;

	UPROPERTY(Transient)
	class UFont*			FontObject;
};
