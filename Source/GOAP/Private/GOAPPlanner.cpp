// Copyright Acinex Games 2021

#include "GOAPPlanner.h"
#include "GOAPNode.h"
#include "GOAPAction.h"
#include "GOAPController.h"
#include "GOAPSettings.h"

UGoapNode UGOAPPlanner::GetLowestFInList(const TArray<UGoapNode>& Nodes) const
{
	float LowestF = MAX_FLT;

	TArray<UGoapNode> Matched;

	for (UGoapNode Node : Nodes)
	{
		if (Node.GetF() < LowestF)
		{
			LowestF = Node.GetF();
			Matched.Empty();
			Matched.Add(Node);
		}

		else if (Node.GetF() == LowestF)
			Matched.Add(Node);
	}

	if (Settings->bSelectRandomAction)
		return Matched[FMath::RandRange(0, Matched.Num() - 1)];

	return Matched[0];
}

TArray<UGoapNode> UGOAPPlanner::GetAdjacent(UGoapNode Current, const TArray<UGOAPAction*>& VisitedActions, APawn* Pawn)
{
	TArray<UGoapNode> Nodes;
	UGoapNode         Adjacent;

	for (int i = 0; i < VisitedActions.Num(); ++i)
	{
		UGOAPAction* const Action                           = VisitedActions[i];
		const bool         bPreconditions                   = Current.GetState().Contains(Action->GetPreconditions());
		const bool         bSameActionAsBefore              = Contains(Current, Action);
		const bool         bProceduralPreconditionFulfilled = Action->CheckPreconditions(Pawn);

		if (bPreconditions && !bSameActionAsBefore && bProceduralPreconditionFulfilled)
		{
			GOAPState State = Current.GetState();
			State.Join(Action->GetEffects());

			Adjacent.SetState(State);
			Adjacent.SetAction(Action);
			Nodes.Push(Adjacent);
		}
	}

	return Nodes;
}

TArray<UGOAPAction*> UGOAPPlanner::GeneratePlan(APawn* Pawn)
{
	if (!Actions.Num())
		return {};

	UGoapNode Start;
	Start.SetState(*Reached);
	Start.SetParentIndex(-1);

	UGoapNode Last;

	OpenList.Empty();
	ClosedList.Empty();
	OpenList.Push(Start);

	bool bGoalReached = false;

	/*
	 * Get cheapest path from actions.
	 */
	while (true)
	{
		UGoapNode Current = GetLowestFInList(OpenList);

		OpenList.Remove(Current);
		ClosedList.Push(Current);
		const int32 Index = ClosedList.Num() - 1;

		if (Current.GetState().Contains(*Goal))
		{
			Last         = Current;
			bGoalReached = true;
			break;
		}

		TArray<UGoapNode> Adjacents = GetAdjacent(Current, Actions, Pawn);

		for (UGoapNode Adjacent : Adjacents)
		{
			/*
			 * Add, if not exists
			 */

			int32 Location = OpenList.Find(Adjacent);

			float F = UGoapNode::GetF(Adjacent, Current);
			if (Location == -1 || OpenList[Location].GetF() > F)
			{
				Adjacent.SetParentIndex(Index);
				Adjacent.SetParent(&Current);

				OpenList.Add(Adjacent);
			}
		}

		if (OpenList.Num() == 0 || ClosedList.Num() > MaxDepth)
			break;
	}

	TArray<UGOAPAction*> Plan;

	if (bGoalReached)
	{
		UGoapNode Node = Last;
		while (Node != Start)
		{
			Plan.Push(Node.GetAction());
			Node = ClosedList[Node.GetParentIndex()];
		}
	}
	return Plan;
}

void UGOAPPlanner::SetMaxDepth(const int32 InMaxDepth)
{
	MaxDepth = InMaxDepth;
}

bool UGOAPPlanner::ContainsNode(const UGoapNode& Node, TArray<UGoapNode> Nodes)
{
	for (UGoapNode Item : Nodes)
		if (Item == Node)
			return true;

	return false;
}

bool UGOAPPlanner::Contains(const UGoapNode& Node, UGOAPAction* const Action)
{
	if (Node.GetAction() == Action)
		return true;

	int32 ParentIndex = Node.GetParentIndex();
	while (ParentIndex >= 0)
	{
		UGoapNode Element = ClosedList[ParentIndex];

		if (Element.GetAction() == Action)
			return true;

		ParentIndex = Element.GetParentIndex();
	}

	return false;
}

void UGOAPPlanner::ShuffleActions()
{
	if (!Settings->bSelectRandomAction)
		return;

	const int32 LastIndex = Actions.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		const int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
			Actions.Swap(i, Index);
	}
}

void UGOAPPlanner::Shuffle(TArray<UGoapNode> Nodes) const
{
	if (!Settings->bSelectRandomAction)
		return;

	const int32 LastIndex = Nodes.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		const int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
			Nodes.Swap(i, Index);
	}
}

void UGOAPPlanner::Initialize(GOAPState* InReached, GOAPState* InGoal, TSet<TSubclassOf<UGOAPAction>> ActionsClasses, int32 InMaxDepth, AGOAPController* Controller)
{
	Reached  = InReached;
	Goal     = InGoal;
	MaxDepth = InMaxDepth;
	Settings = GetDefault<UGOAPSettings>();

	for (TSubclassOf<UGOAPAction> ActionClass : ActionsClasses)
	{
		if (!ActionClass)
			continue;

		UGOAPAction* Action = NewObject<UGOAPAction>(Controller, ActionClass);
		Action->Initialize();

		Actions.Push(Action);
	}

	if (!ActionsClasses.Num())
	UE_LOG(LogTemp, Warning, TEXT("No Actions defined for %s"), *Controller->GetName());
}
