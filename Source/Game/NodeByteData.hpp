#pragma once
#include <vector>
#include <string>
#include "Node.h"

struct BytePin
{
	int nodeId = 0;
	int id = 0;
	char text[256]{};
	PinDirection direction = PinDirection::None;
	PinType type = PinType::Unknown;
};

struct ByteNode
{
	char name[256]{};
	char category[256]{};
	eNodeType type = eNodeType::None;
	int id = 0;
	bool isStartNode = false;
};