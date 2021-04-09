// Copyright Acinex Games 2021

#pragma once

#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "GOAPActionResult.h"
#include "GOAPGoal.h"
#include "GOAPState.h"
#include "AIModule/Classes/AITypes.h"
#include "GOAPAction.generated.h"

/**
 * Represents an action inside the action plan
 */
UCLASS(Abstract, Blueprintable, config=Game)
class GOAP_API UGOAPAction : public UObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	float GetCost();

	/** Executes the action. If the result is success, the effects will be applied */
	UFUNCTION(BlueprintNativeEvent)
	void Execute(APawn* Pawn);

	void TickAction(APawn* Pawn, float DeltaSeconds);

	EGOAPActionResult GetResult() const { return Result; }

	/** Hook for checking if the Pawn can currently do this action. This is checked before choosing the action */
	UFUNCTION(BlueprintNativeEvent)
	bool CheckPreconditions(APawn* Pawn);

	GOAPState GetPreconditions() const;
	GOAPState GetEffects() const;

	void Initialize();

protected:
	/** If any of the Tick functions is implemented, how often should they be ticked.
	*	Values < 0 mean 'every tick'. */
	UPROPERTY(EditAnywhere, Category = Task)
	FIntervalCountdown TickInterval;

	/** Determines how expensive it is for the algorithm to choose this action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Cost;

	/** Conditions has to be met before this action can be chosen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGOAPGoal> Preconditions;

	/** Effects, this action will apply if successfully executed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGOAPGoal> Effects;

	UFUNCTION(BlueprintImplementableEvent)
    void Tick(APawn* Pawn, float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void FinishExecute(bool bSuccess);

private:
	GOAPState PreconditionState;
	GOAPState EffectState;

	EGOAPActionResult Result = EGOAPActionResult::Continue;
};
