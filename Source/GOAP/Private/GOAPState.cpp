// Copyright Acinex Games 2021

#include "GOAPState.h"

GOAPState::GOAPState()
{
}

GOAPState::~GOAPState()
{
}

GOAPState::GOAPState(std::map<FString, float>& Vertices)
{
	SetVertices(Vertices);
}

const std::map<FString, float>& GOAPState::GetVertices() const
{
	return Vertices;
}

bool GOAPState::operator==(GOAPState Other) const
{
	return Vertices.size() == Other.Vertices.size() && std::equal(Vertices.begin(), Vertices.end(), Other.Vertices.begin());
}

bool GOAPState::Contains(GOAPState Other) const
{
	for (auto Requirement : Other.Vertices)
	{
		auto Iterator = Vertices.find(Requirement.first);

		if (Iterator == Vertices.end() || Iterator->second != Requirement.second)
			return false;
	}

	return true;
}

void GOAPState::Join(GOAPState Other)
{
	for (auto Atom : Other.Vertices)
		Vertices[Atom.first] = Atom.second;
}

void GOAPState::SetVertices(std::map<FString, float>& InVertices)
{
	Vertices = InVertices;
}

void GOAPState::AddVertex(const FString Name, const float Value)
{
	Vertices[Name] = Value;
}

void GOAPState::Clear()
{
	Vertices.clear();
}

bool GOAPState::IsEmpty() const
{
	return Vertices.size() == 0;
}

FString GOAPState::ToString() const
{
	FString String = "State [";

	bool bAdded = false;
	for (auto Atom : Vertices)
	{
		if (bAdded)
			String.Append(", ");

		bAdded = true;
		String.Append(Atom.first).Append(":").Append(FString::SanitizeFloat(Atom.second));
	}

	return String.Append("]");
}
