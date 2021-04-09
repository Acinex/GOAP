// Copyright Acinex Games 2021

#include "GOAPNode.h"

#include "GOAPAction.h"
#include "GOAPState.h"


GOAPState UGoapNode::GetState() const
{
	return State;
}

void UGoapNode::SetState(const GOAPState InState)
{
	State = InState;
}

UGOAPAction* UGoapNode::GetAction() const
{
	return Action;
}

void UGoapNode::SetAction(UGOAPAction* InAction)
{
	Action           = InAction;
	G                = Action->GetCost();
	H                = 0;
}


int32 UGoapNode::GetH() const
{
	return H;
}

int32 UGoapNode::GetH(const UGoapNode From, const GOAPState With)
{
	float H = From.GetH();
	for (auto Pair : From.State.GetVertices())
	{
		auto Tree_Const_Iterator = With.GetVertices().find(Pair.first);

		if (Tree_Const_Iterator != With.GetVertices().end())
		{
			if (Pair.second != Tree_Const_Iterator->second)
				H++;
		}
		else
		{
			H++;
		}
	}

	return H;
}

float UGoapNode::GetG() const
{
	return G;
}

int32 UGoapNode::GetParentIndex() const
{
	return ParentIndex;
}

void UGoapNode::SetParentIndex(const int32 InParentIndex)
{
	ParentIndex = InParentIndex;
}

void UGoapNode::SetParent(UGoapNode* Value)
{

	G += Value->G;
	H = GetH(*this, Value->State);
}

float UGoapNode::GetF() const
{
	return G + H;
}

float UGoapNode::GetF(const UGoapNode From, const UGoapNode With)
{
	const float G = With.GetG() + From.GetG();
	const float H = GetH(From, With.GetState());
	return G + H;
}

FString UGoapNode::ToString() const
{
	FString String = TEXT("Node [");

	if (Action)
		String.Append("Action: ").Append(Action->GetName());
	else
		String.Append("Action: null");

	String.Append(", State: ").Append(State.ToString());

	return String.Append("]");
}
