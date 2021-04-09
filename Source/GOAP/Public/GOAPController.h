// Copyright Acinex Games 2021

#pragma once

#include "CoreMinimal.h"

#include "GOAPGoal.h"
#include "GOAPAction.h"
#include "GOAPState.h"
#include "AIController.h"
#include "GOAPController.generated.h"

class UGOAPPlanner;
class UGOAPSettings;

UCLASS(Config=GOAP, defaultconfig)
class GOAP_API AGOAPController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGOAPController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = GOAP)
	void UpdateGoals(const TArray<FGOAPGoal>& Goals);

	UFUNCTION(BlueprintCallable, Category = GOAP)
	void SetGoals(const TArray<FGOAPGoal>& Goals);

	UFUNCTION(BlueprintCallable, Category = GOAP)
	void UpdateReachedGoals(const TArray<FGOAPGoal>& Goals);

	UFUNCTION(BlueprintCallable, Category = GOAP)
	void SetReachedGoals(const TArray<FGOAPGoal>& Goals);

	UFUNCTION(BlueprintPure, Category = GOAP)
	UGOAPAction* GetCurrentAction() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GOAP)
	TArray<FGOAPGoal> ReachedGoals;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GOAP)
	TArray<FGOAPGoal> DesiredGoals;

	/** Actions the character can perform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GOAP)
	TSet<TSubclassOf<UGOAPAction>> ActionClasses;

	/** Max depth of the tree */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GOAP)
	int32 MaxDepth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GOAP)
	bool bExecuteEveryTick = true;

	UPROPERTY()
	TArray<UGOAPAction*> Actions;

	UPROPERTY()
	TArray<UGOAPAction*> Plan;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool ExecuteGoalOrientatedActionPlan();

private:

	UGOAPPlanner* Planner;
	GOAPState     ReachedState;
	GOAPState     DesiredState;
	bool          bIsContinuous;

	UPROPERTY()
	const UGOAPSettings* Settings;

	bool GeneratePlan();
};
