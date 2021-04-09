// Copyright Acinex Games 2021

#pragma once
#include "GOAPState.h"

class UGOAPAction;
class GOAPState;

class UGoapNode
{
	int32 ParentIndex = -1;
	int32 H           = 0;
	float G           = 0.0F;

	UGOAPAction* Action = nullptr;
	GOAPState    State;

public:
	GOAPState GetState() const;

	void SetState(GOAPState InState);

	UGOAPAction* GetAction() const;
	void         SetAction(UGOAPAction* InAction);

	bool operator==(UGoapNode const& Other) const
	{
		return GetAction() == Other.GetAction();
	}

	bool operator!=(UGoapNode const& Other) const
	{
		return GetAction() != Other.GetAction();
	}

	int32        GetH() const;
	static int32 GetH(UGoapNode From, GOAPState With);

	float GetG() const;

	int32 GetParentIndex() const;
	void  SetParentIndex(int32 InParentIndex);
	void  SetParent(UGoapNode* Value);

	float        GetF() const;
	static float GetF(UGoapNode From, UGoapNode With);

	FString ToString() const;
};
