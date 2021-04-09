// Copyright Acinex Games 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GOAPSettings.generated.h"

class UGOAPAction;
/**
 * 
 */
UCLASS(Config=GOAP, DefaultConfig)
class GOAP_API UGOAPSettings : public UObject
{
	GENERATED_BODY()
public:
	/**
	 *Setting this to true will select a random action when they have the same cost.
	 *Otherwise the first found will be selected
	 */
	UPROPERTY(EditAnywhere, Config, Category = Actions, meta=(DisplayName="Select random Action"))
	bool bSelectRandomAction = true;

	/** Every Controller will automatically add those actions to his own list */
	UPROPERTY(EditAnywhere, Config, Category=Actions, meta=(DisplayName="Default actions for every controller"))
	TArray<TSubclassOf<UGOAPAction>> DefaultActions;
};
