#include "stdafx.h"
#include "Node.h"
#include "NodeGraph.h"
#include "NodeGraphManager.h"

Node::~Node()
{
	for (Pin* pin : mPins)
	{
		delete pin;
		pin = nullptr;
	}
	mPins.clear();
}

int Node::Run()
{
	return 0;
}

void Node::SetId(const int& aId)
{
	mId = aId;
}

void Node::SetName(const std::string& aName)
{
	mName = aName;
}

void Node::SetCategory(const std::string& aCategory)
{
	mCategory = aCategory;
}

void Node::SetType(eNodeType aType)
{
	mType = aType;
}

void Node::SetPins(const std::vector<Pin*>& aPins)
{
	mPins = aPins;
}

void Node::SetGraph(NodeGraph* aGraph)
{
	mGraph = aGraph;
}

void Node::SetStartNode()
{
	mIsStartNode = true;
}

void Node::CreatePin(std::string aLabel, PinType aType, PinDirection aDirection)
{
	auto nM = NodeGraphManager::Get();
	Pin* pin = new Pin(this, nM->GetId(), aLabel, aType, aDirection);
	nM->IncrementId();

	switch (aType)
	{
	case PinType::Bool:
	{
		bool b = false;
		pin->data = b;
		break;
	}
	case PinType::Int:
	{
		int i = 0;
		pin->data = i;
		break;
	}
	case PinType::Float:
	{
		float f = 0.f;
		pin->data = f;
		break;
	}
	case PinType::String:
	{
		std::string s = "";
		pin->data = s;
		break;
	}
	default:
		break;
	}
	
	mPins.push_back(pin);
	++mNextId;
}

std::any Node::GetPinData(const int aPinIndex)
{
	for (Link& link : mGraph->GetLinks())
	{
		if (link.endPin == mPins[aPinIndex]->id)
		{
			for (Pin* pin : link.startNode->GetPins())
			{
				if (pin->id == link.startPin)
				{
					return pin->data;
				}
			}
		}
	}

	return mPins[aPinIndex]->data;
}
