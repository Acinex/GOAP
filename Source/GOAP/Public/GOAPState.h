// Copyright Acinex Games 2021

#pragma once
#include <map>

class GOAP_API GOAPState
{
	std::map<FString, float> Vertices;

public:
	GOAPState();

	~GOAPState();

	GOAPState(std::map<FString, float>& Vertices);

	const std::map<FString, float>& GetVertices() const;

	bool operator==(GOAPState Other) const;

	bool Contains(GOAPState Other) const;
	void Join(GOAPState Other);

	void SetVertices(std::map<FString, float>& InVertices);
	void AddVertex(FString Name, float Value);
	void Clear();
	bool IsEmpty() const;
	
	FString ToString() const;
};
