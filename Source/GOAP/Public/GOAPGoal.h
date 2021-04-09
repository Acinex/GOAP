// Copyright Acinex Games 2021

#pragma once
#include "GOAPGoal.generated.h"

USTRUCT(BlueprintType)
struct GOAP_API FGOAPGoal
{
	GENERATED_BODY()

	/**
	 * Name this goal.
	 * We selected a FText to allow you to select from a StringTable to minimize mistakes from typos
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	/** Defines the value of this goal. It is a float to be able to reach multiple stages of something.
	 * For example hunger:
	 * If the character has a hunger of 2 he can choose different actions from when he just has 1.
	 * Still can be used as a bool by using 0 and 1
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
