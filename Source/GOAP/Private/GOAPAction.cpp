// Copyright Acinex Games 2021

#include "GOAPAction.h"

#include "GOAPActionResult.h"

float UGOAPAction::GetCost_Implementation()
{
	return Cost;
}

void UGOAPAction::Execute_Implementation(APawn* Pawn)
{
}

UWorld* UGOAPAction::GetWorld() const
{
	if (GetOuter() == nullptr)
		return nullptr;

	// Special case for behavior tree nodes in the editor
	if (Cast<UPackage>(GetOuter()) != nullptr)
		// GetOuter should return a UPackage and its Outer is a UWorld
		return Cast<UWorld>(GetOuter()->GetOuter());

	// In all other cases...
	return GetOuter()->GetWorld();
}

void UGOAPAction::TickAction(APawn* Pawn, float DeltaSeconds)
{
	if (TickInterval.Tick(DeltaSeconds))
	{
		DeltaSeconds = TickInterval.GetElapsedTimeWithFallback(DeltaSeconds);

		Tick(Pawn, DeltaSeconds);

		TickInterval.Reset();
	}
}

GOAPState UGOAPAction::GetPreconditions() const
{
	return PreconditionState;
}

GOAPState UGOAPAction::GetEffects() const
{
	return EffectState;
}

bool UGOAPAction::CheckPreconditions_Implementation(APawn* Pawn)
{
	return true;
}

void UGOAPAction::Initialize()
{
	for (FGOAPGoal Precondition : Preconditions)
		PreconditionState.AddVertex(Precondition.Name.ToString(), Precondition.Value);

	for (FGOAPGoal Effect : Effects)
		EffectState.AddVertex(Effect.Name.ToString(), Effect.Value);
}

void UGOAPAction::FinishExecute(bool bSuccess)
{
	Result = bSuccess ? EGOAPActionResult::Complete : EGOAPActionResult::Cancel;
}
