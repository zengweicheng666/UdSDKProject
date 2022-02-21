// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UdSDKProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UDSDKPROJECT_API AUdSDKProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
