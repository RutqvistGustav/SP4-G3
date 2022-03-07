#pragma once
#include <unordered_map>
#include "Node.h"

/* NodeTypes */
#include "NodeConsolePrint.h"
#include "NodeStart.h"
#include "NodeFloat.h"
#include "NodeAdditionFloat.h"
#include "NodeBranch.h"
#include "NodeConsolePrintFloat.h"
#include "NodeCompareInt.h"
#include "NodeInt.h"
#include "NodeBool.h"
#include "NodeInput.h"
#include "NodeCurrentButton.h"
#include "NodeButtonClicked.h"

class NodeRegistry
{
public:
	static void RegisterTypes()
	{
		RegisterType<ConsolePrint>();
		RegisterType<NodeStart>();
		RegisterType<AdditionFloat>();
		RegisterType<NodeBranch>();
		RegisterType<ConsolePrintFloat>();
		RegisterType<NodeFloat>();
		RegisterType<NodeCompareInt>();
		RegisterType<NodeInt>();
		RegisterType<NodeBool>();
		RegisterType<NodeInput>();
		RegisterType<NodeCurrentButton>();
		RegisterType<NodeButtonClicked>();
	}

	static Node* CreateNode(eNodeType aType, const int aId, NodeGraph* aGraph)
	{
		Node* newNode = nullptr;

		switch (aType)
		{
		case eNodeType::None:
			break;
		case eNodeType::ConsolePrint:
			newNode = new ConsolePrint(aId, aGraph);
			break;
		case eNodeType::Start:
			newNode = new NodeStart(aId, aGraph);
			break;
		case eNodeType::Float:
			newNode = new NodeFloat(aId, aGraph);
			break;
		case eNodeType::Int:
			newNode = new NodeInt(aId, aGraph);
			break;
		case eNodeType::Bool:
			newNode = new NodeBool(aId, aGraph);
			break;
		case eNodeType::AdditionFloat:
			newNode = new AdditionFloat(aId, aGraph);
			break;
		case eNodeType::Branch:
			newNode = new NodeBranch(aId, aGraph);
			break;
		case eNodeType::ConsolePrintFloat:
			newNode = new ConsolePrintFloat(aId, aGraph);
			break;
		case eNodeType::CompareInt:
			newNode = new NodeCompareInt(aId, aGraph);
			break;
		case eNodeType::Input:
			newNode = new NodeInput(aId, aGraph);
			break;
		case eNodeType::CurrentButton:
			newNode = new NodeCurrentButton(aId, aGraph);
			break;
		case eNodeType::ButtonClicked:
			newNode = new NodeButtonClicked(aId, aGraph);
			break;
		}

		return newNode;
	}

	static Node* CreateNode(const Node& aNode, NodeGraph* aGraph)
	{
		Node* newNode = nullptr;

		switch (aNode.GetNodeType())
		{
		case eNodeType::None:
			break;
		case eNodeType::ConsolePrint:
			newNode = new ConsolePrint(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::ConsolePrint, aNode.GetId(), aGraph);
			break;
		case eNodeType::Start:
			newNode = new NodeStart(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Start, aNode.GetId(), aGraph);
			break;
		case eNodeType::Float:
			newNode = new NodeFloat(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Float, aNode.GetId(), aGraph);
			break;
		case eNodeType::Int:
			newNode = new NodeInt(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Int, aNode.GetId(), aGraph);
			break;
		case eNodeType::Bool:
			newNode = new NodeBool(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Bool, aNode.GetId(), aGraph);
			break;
		case eNodeType::AdditionFloat:
			newNode = new AdditionFloat(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::AdditionFloat, aNode.GetId(), aGraph);
			break;
		case eNodeType::Branch:
			newNode = new NodeBranch(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Branch, aNode.GetId(), aGraph);
			break;
		case eNodeType::ConsolePrintFloat:
			newNode = new ConsolePrintFloat(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::ConsolePrintFloat, aNode.GetId(), aGraph);
			break;
		case eNodeType::CompareInt:
			newNode = new NodeCompareInt(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::CompareInt, aNode.GetId(), aGraph);
			break;
		case eNodeType::Input:
			newNode = new NodeInput(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::Input, aNode.GetId(), aGraph);
			break;
		case eNodeType::CurrentButton:
			newNode = new NodeCurrentButton(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::CurrentButton, aNode.GetId(), aGraph);
			break;
		case eNodeType::ButtonClicked:
			newNode = new NodeButtonClicked(aNode.GetPins(), aNode.GetNodeName(), aNode.GetNodeCategory(), eNodeType::ButtonClicked, aNode.GetId(), aGraph);
			break;
		}

		return newNode;
	}
	static Node** GetNodeTypes()
	{
		return myTypes;
	}

	static const unsigned short GetNodeTypeCount()
	{
		return myTypeCounter; 
	}

	template <class T>
	static void RegisterType()
	{
		myTypes[myTypeCounter] = new T;
		myTypes[myTypeCounter]->SetId(myTypeCounter);
		myTypeCounter++;
	}

	static void Destroy()
	{
		do
		{
			delete myTypes[--myTypeCounter];
			myTypes[myTypeCounter] = nullptr;
		} while (myTypeCounter != 0);
	}

	static Node* myTypes[128];
	static unsigned short myTypeCounter;
};