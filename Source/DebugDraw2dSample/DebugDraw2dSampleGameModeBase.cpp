// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugDraw2dSampleGameModeBase.h"

// for UCanvas.
// for UDebugDrawService.
#include "Engine.h"


/*==========================================================================*/
/*==========================================================================*/
ADebugDraw2dSampleGameModeBase::ADebugDraw2dSampleGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UFont> font(TEXT("/Engine/EngineFonts/Roboto"));
	FontObject = font.Object;
}

/*==========================================================================*/
/*==========================================================================*/
void ADebugDraw2dSampleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	auto drawDebugDelegate = FDebugDrawDelegate::CreateUObject(this, &ADebugDraw2dSampleGameModeBase::Draw);
	if (drawDebugDelegate.IsBound())
	{
		this->DrawDebugDelegateHandle = UDebugDrawService::Register(TEXT("GameplayDebug"), drawDebugDelegate);
	}
}

/*==========================================================================*/
/*==========================================================================*/
void ADebugDraw2dSampleGameModeBase::BeginDestroy()
{
	if (this->DrawDebugDelegateHandle.IsValid())
	{
		UDebugDrawService::Unregister(this->DrawDebugDelegateHandle);
		this->DrawDebugDelegateHandle.Reset();
	}

	Super::BeginDestroy();
}


/*==========================================================================*/
/*==========================================================================*/
void ADebugDraw2dSampleGameModeBase::Draw(UCanvas* InCanvas, APlayerController* InPC)
{
	if (!InCanvas || !InCanvas->Canvas)
	{
		return;
	}

	//UWorld* world = this->GetWorld();
	//if (!world)
	//{
	//	return;
	//}
	//if (world == InCanvas->Canvas->GetScene()->GetWorld())
	//{// このActorのワールド.
	//}
	//else
	//{// Editorのウィンドウなら何もしない.
	//	return;
	//}

	auto pc = InPC;
	if (pc == nullptr)
	{
		// [memo]
		// InPC は引数はあるけど呼び出し元で nullptr 固定されているので使用できない.
		UGameInstance* const gameInstance = UGameplayStatics::GetGameInstance(this/*WorldContextObject*/);
		pc = gameInstance ? gameInstance->GetFirstLocalPlayerController() : nullptr;
	}

	// font 描画.
	{
		FString dispString;
		if (pc != nullptr && pc->GetPawn() != nullptr)
		{
			dispString = FString::Printf(TEXT("pawn pos (%s)\npc rot (%s)"), *pc->GetPawn()->GetActorLocation().ToString(), *pc->GetControlRotation().ToString());
		}
		else
		{
			dispString = FString::Printf(TEXT("no pc"));
		}

		FCanvasTextItem item(FVector2D(32.0f, 64.0f), FText::FromString(dispString), this->FontObject, FLinearColor::Red);
		InCanvas->DrawItem(item);
	}

	// line 描画.
	{
		FCanvasLineItem item(FVector2D(28.0f, 110.0f), FVector2D(90.0f, 110.0f));
		item.SetColor(FLinearColor::Blue);
		item.BlendMode = SE_BLEND_Opaque;
		item.LineThickness = 2.0f;
		InCanvas->DrawItem(item);
	}
	// line 描画2( 3D上の点までのライン )
	{
		FVector2D screenLocation;
		if (UGameplayStatics::ProjectWorldToScreen(pc, FVector(400.0f, 0.0f, 20.0f), screenLocation, false/*bPlayerViewportRelative*/))
		{
			FCanvasLineItem item(FVector2D(90.0f, 110.0f), screenLocation);
			item.SetColor(FLinearColor::Green);
			InCanvas->DrawItem(item);
		}
	}

	// box 描画.
	{
		FVector2D Pos(32.0f, 120.0f);
		FVector2D Size(96.0f, 32.0f);
		FLinearColor Color(1.0f, 1.0f, 1.0f, 0.5f);
		FCanvasTileItem tileItem(Pos, Size, Color);
		if (Color.A != 1.0f)
		{
			tileItem.BlendMode = SE_BLEND_Translucent;
		}
		InCanvas->DrawItem(tileItem);
	}
}