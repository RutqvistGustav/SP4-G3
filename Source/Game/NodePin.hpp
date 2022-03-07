#pragma once
#include "stdafx.h"
#include "imgui.h"
#include <any>

class Node;

enum class PinType
{
	Unknown,
	Bool,
	Int,
	Float,
	String,
	Exec
};

struct PinColor
{
	static ImColor GetColor(PinType aType)
	{
		switch (aType)
		{
		case PinType::Bool:		return ImColor(220, 48, 48);
		case PinType::Int:		return ImColor(68, 201, 156);
		case PinType::Float:	return ImColor(147, 226, 74);
		case PinType::String:	return ImColor(124, 21, 153);
		case PinType::Exec:		return ImColor(255, 255, 255);
		case PinType::Unknown:		return ImColor(255, 0, 0);
		}
	}
};

enum class PinDirection
{
	None,
	In,
	Out
};

struct Pin
{
public:
	Pin(Node* aNode, const unsigned int aId, const std::string& aText, PinType aType, PinDirection aDirection)
	{
		parent = aNode;
		id = aId;
		text = aText;
		direction = aDirection;
		type = aType;
	
	}

	Node* parent;
	std::any data;
	int id;
	std::string text;
	PinDirection direction;
	PinType type;
};