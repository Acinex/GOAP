// Copyright Acinex Games 2021

#pragma once
#include "GOAPNode.h"

class AGOAPController;
class UGOAPSettings;
class UGOAPAction;
class GOAPState;

class GOAP_API UGOAPPlanner
{
public:
	/** Get the node with the lowest value of F */
	UGoapNode GetLowestFInList(const TArray<UGoapNode>& Nodes) const;
	void      Initialize(GOAPState* InReached, GOAPState* InGoal, TSet<TSubclassOf<UGOAPAction>> ActionsClasses, int32 InMaxDepth, AGOAPController* Controller);

	/** Returns the nodes adjacent to the current one */
	TArray<UGoapNode> GetAdjacent(UGoapNode Current, const TArray<UGOAPAction*>& VisitedActions, APawn* Pawn);

	/** A* pathfinding algorithm */
	TArray<UGOAPAction*> GeneratePlan(APawn* Pawn);

	void SetMaxDepth(int32 InMaxDepth);

private:
	GOAPState* Reached = nullptr;
	GOAPState* Goal    = nullptr;

	TArray<UGOAPAction*> Actions;

	TArray<UGoapNode> OpenList;
	TArray<UGoapNode> ClosedList;

	int32                MaxDepth = 0;
	const UGOAPSettings* Settings;

	static bool ContainsNode(const UGoapNode& Node, TArray<UGoapNode> Nodes);
	bool               Contains(const UGoapNode& Node, UGOAPAction* const Action);

	void ShuffleActions();
	void Shuffle(TArray<UGoapNode> Nodes) const;
};