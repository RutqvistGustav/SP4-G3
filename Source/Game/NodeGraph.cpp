#include "stdafx.h"
#include "NodeGraph.h"
#include "Node.h"
#include "NodeStart.h"

NodeGraph::NodeGraph() :
	mName(""),
	mInput(nullptr)
{
}

NodeGraph::NodeGraph(const std::string& aName) :
	mName(aName),
	mInput(nullptr)
{
}

NodeGraph::~NodeGraph()
{
	Clear();
}

void NodeGraph::Init()
{
}

void NodeGraph::Update(const UpdateContext& aContext)
{
	mInput = aContext.myInput;

	for (int i = 0; i < mStartNodes.size(); ++i)
	{
		if (mStartNodes[i].first == false) continue;

		if (mStartNodes[i].second->GetNodeType() != eNodeType::Start) continue;

		bool looping = std::any_cast<bool>(mStartNodes[i].second->GetPins()[LOOP_PIN_ID]->data);

		if (looping)
		{
			RunNode(mStartNodes[i].second);
		}
	}
}

void NodeGraph::Clear()
{
	for (int i = 0; i < mStartNodes.size(); ++i)
	{
		mStartNodes[i].second = nullptr;
	}
	mStartNodes.clear();

	for (Node* node : mNodes)
	{
		delete node;
		node = nullptr;
	}
	mNodes.clear();

	mLinks.clear();
}

void NodeGraph::RunStart(Node* aNode)
{
	for (int i = 0; i < mStartNodes.size(); ++i)
	{
		if (aNode == mStartNodes[i].second)
		{
			RunNode(mStartNodes[i].second);
			mStartNodes[i].first = true;
		}
	}
}

void NodeGraph::RunStartNodes()
{
	for (int i = 0; i < mStartNodes.size(); ++i)
	{
		RunNode(mStartNodes[i].second);
		mStartNodes[i].first = true;
	}
}

const std::vector<Pin*> NodeGraph::GetAllPins()
{
	std::vector<Pin*> pins;

	for (Node* node : mNodes)
	{
		for (Pin* pin : node->GetPins())
		{
			pins.push_back(pin);
		}
	}

	return pins;
}

std::vector<Link>& NodeGraph::GetLinks()
{
	return mLinks;
}

void NodeGraph::SetName(const std::string& aName)
{
	mName = aName;
}

void NodeGraph::AddNode(Node* aNode)
{
	if (aNode->IsStartNode())
	{
		std::pair node = { false, aNode };
		if (aNode->GetNodeType() == eNodeType::Start)
		{
			node.first = true;
		}
		mStartNodes.push_back(node);
	}

	mNodes.push_back(aNode);
}

void NodeGraph::RemoveNode(const int aId)
{
	for (int i = 0; i < mStartNodes.size(); ++i)
	{
		if (mStartNodes[i].second->GetId() == aId)
		{
			mStartNodes.erase(mStartNodes.begin() + i);
			continue;
		}
	}

	for (int i = 0; i < mNodes.size(); ++i)
	{
		if (mNodes[i]->GetId() == aId)
		{
			for (int j = 0; j < mLinks.size(); ++j)
			{
				if (mLinks[j].startNode == mNodes[i])
				{
					RemoveLink(mLinks[j].id);
				}
			}

			Node* node = mNodes[i];
			mNodes.erase(mNodes.begin() + i);
			delete node;
			node = nullptr;
			return;
		}
	}
}

void NodeGraph::AddLink(Link& aLink)
{
	mLinks.push_back(aLink);
}

void NodeGraph::RemoveLink(const int aId)
{
	for (int i = 0; i < mLinks.size(); ++i)
	{
		if (mLinks[i].id == aId)
		{
			mLinks.erase(mLinks.begin() + i);
		}
	}
}

int NodeGraph::RunNode(Node* aNode)
{
	int pinIndex = aNode->Run();

	if (pinIndex == -1) return pinIndex;

	for (Link& link : mLinks)
	{
		if (aNode->GetPins()[pinIndex]->direction == PinDirection::Out)
		{
			if (link.startPin == aNode->GetPins()[pinIndex]->id)
			{
				RunNode(link.endNode);
			}
		}
	}

	return -1;
}
