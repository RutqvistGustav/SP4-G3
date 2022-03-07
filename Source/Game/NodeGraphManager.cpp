#include "stdafx.h"
#include "NodeGraphManager.h"

#include <fstream>
#include <ios>
#include <filesystem>

#include "NodeGraph.h"
#include "Node.h"
#include "NodeRegistry.h"
#include "NodeByteData.hpp"
#include "GlobalServiceProvider.h"

NodeGraphManager* NodeGraphManager::ourInstance = nullptr;

NodeGraphManager::NodeGraphManager() :
	  mCurrentId(0)
	, mGraphLoaded(false)
{
}

NodeGraphManager::~NodeGraphManager()
{
	for (NodeGraph* graph : mGraphs)
	{
		delete graph;
		graph = nullptr;
	}
}

NodeGraphManager* NodeGraphManager::Get()
{
	if (!ourInstance)
	{
		ourInstance = new NodeGraphManager();
	}
	return ourInstance;
}

void NodeGraphManager::Init(GlobalServiceProvider* aGlobalServiceProvider)
{
	mGSP = aGlobalServiceProvider;

	LoadGraphs();
}

void NodeGraphManager::Update(const UpdateContext& aContext)
{
	for (auto& graph : mGraphs)
	{
		graph->Update(aContext);
	}
}

void NodeGraphManager::AddGraph(NodeGraph* aGraph)
{
	mGraphs.push_back(aGraph);
}

NodeGraph* NodeGraphManager::LoadGraph(const std::string& aGraphName)
{
	Deserialize(aGraphName);

	for (auto& graph : mGraphs)
	{
		if (graph->GetName() == aGraphName)
		{
			mGraphLoaded = true;
			return graph;
		}
	}

	return nullptr;
}

NodeGraph* NodeGraphManager::GetGraph(const std::string& aGraphName)
{
	for (auto& graph : mGraphs)
	{
		if (graph->GetName() == aGraphName) return graph;
	}

	NodeGraph* newGraph = new NodeGraph(aGraphName);
	mGraphs.push_back(newGraph);

	return newGraph;
}

void NodeGraphManager::IncrementId()
{
	++mCurrentId;
}

void NodeGraphManager::SaveGraph(NodeGraph* aGraph)
{
	Serialize(aGraph);
}

void NodeGraphManager::RemoveGraph(NodeGraph* aGraph)
{
	for (int i = 0; i < mGraphs.size(); ++i)
	{
		if (mGraphs[i] == aGraph)
		{
			mGraphs.erase(mGraphs.begin() + i);
			delete aGraph;
			aGraph = nullptr;
			return;
		}
	}
}

void NodeGraphManager::RemoveGraph(const std::string& aGraph)
{
	for (int i = 0; i < mGraphs.size(); ++i)
	{
		if (mGraphs[i]->GetName() == aGraph)
		{
			NodeGraph* graph = mGraphs[i];
			mGraphs.erase(mGraphs.begin() + i);
			delete graph;
			graph = nullptr;
			return;
		}
	}
}

void NodeGraphManager::SetGraphLoaded(const bool aValue)
{
	mGraphLoaded = aValue;
}

void NodeGraphManager::LoadGraphs()
{
	std::string ext(".bytes");
	for (auto& p : std::filesystem::recursive_directory_iterator(mFolderPath))
	{
		if (p.path().extension() == ext)
		{
			std::string name = p.path().stem().string();
			mGraphs.push_back(new NodeGraph(name));
			Deserialize(name);
		}
	}

	for (NodeGraph* graph : mGraphs)
	{
		graph->Init();
	}
}

void NodeGraphManager::ConvertNodesToBytes(NodeGraph* aGraph, std::vector<ByteNode>& aByteNodes, std::vector<BytePin>& aBytePins)
{
	auto& nodes = aGraph->GetNodes();

	aByteNodes.resize(nodes.size());

	int i = 0;
	for (i = 0; i < nodes.size(); ++i)
	{
		strcpy_s(aByteNodes[i].category, nodes[i]->GetNodeCategory().c_str());
		strcpy_s(aByteNodes[i].name, nodes[i]->GetNodeName().c_str());
		aByteNodes[i].id = nodes[i]->GetId();
		aByteNodes[i].isStartNode = nodes[i]->IsStartNode();
		aByteNodes[i].type = nodes[i]->GetNodeType();	

		for (Pin* pin : nodes[i]->GetPins())
		{
			BytePin bytePin;
			
			bytePin.nodeId = nodes[i]->GetId();

			bytePin.direction = pin->direction;
			bytePin.id = pin->id;
			bytePin.type = pin->type;
			strcpy_s(bytePin.text, pin->text.c_str());

			aBytePins.push_back(bytePin);
		}
	}
}

void NodeGraphManager::Serialize(NodeGraph* aGraph)
{
	std::vector<ByteNode> byteNodes;
	std::vector<BytePin> bytePins;
	ConvertNodesToBytes(aGraph, byteNodes, bytePins);

	std::string fileName = mFolderPath + aGraph->GetName() + ".bytes";

	std::fstream fout(
		fileName, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

	const size_t numPins = bytePins.size();
	fout.write(reinterpret_cast<const char*>(&numPins), static_cast<std::streamsize>(sizeof(size_t)));

	const size_t numNodes = byteNodes.size();
	fout.write(reinterpret_cast<const char*>(&numNodes), static_cast<std::streamsize>(sizeof(size_t)));
	fout.write(reinterpret_cast<const char*>(byteNodes.data()), static_cast<std::streamsize>(sizeof(ByteNode) * numNodes));

	fout.write(reinterpret_cast<const char*>(&numPins), static_cast<std::streamsize>(sizeof(size_t)));
	fout.write(reinterpret_cast<const char*>(bytePins.data()),	static_cast<std::streamsize>((sizeof(BytePin) * numPins)));

	const size_t numLinks = aGraph->GetLinks().size();
	fout.write(reinterpret_cast<const char*>(&numLinks), static_cast<std::streamsize>(sizeof(size_t)));
	fout.write(reinterpret_cast<const char*>(aGraph->GetLinks().data()), static_cast<std::streamsize>(sizeof(Link) * numLinks));

	fout.write(reinterpret_cast<const char*>(&mCurrentId), static_cast<std::streamsize>(sizeof(int)));

	for (Pin* pin : aGraph->GetAllPins())
	{
		const char* data;

		switch (pin->type)
		{
		case PinType::Bool:
			fout.write(reinterpret_cast<const char*>(std::any_cast<bool>(&pin->data)), static_cast<std::streamsize>(sizeof(bool)));
			break;
		case PinType::Int:
			fout.write(reinterpret_cast<const char*>(std::any_cast<int>(&pin->data)), static_cast<std::streamsize>(sizeof(int)));
			break;
		case PinType::Float:
			fout.write(reinterpret_cast<const char*>(std::any_cast<float>(&pin->data)), static_cast<std::streamsize>(sizeof(float)));
			break;
		case PinType::String:
			char buf[256];
			data = std::any_cast<std::string>(&pin->data)->c_str();
			strcpy_s(buf, data);
			fout.write(reinterpret_cast<const char*>(buf), static_cast<std::streamsize>(256));
			break;
		default:
			data = "";
			break;
		}
	}

	fout.close();
}

void NodeGraphManager::Deserialize(const std::string& aGraphName)
{
	NodeGraph* graph = nullptr;
	
	bool exists = false;
	for (auto& g : mGraphs)
	{
		if (aGraphName == g->GetName())
		{
			graph = g;
			exists = true;
			break;
		}
	}

	if (!exists)
	{
		graph = new NodeGraph(aGraphName);
		mGraphs.push_back(graph);
		return;
	}

	graph->Clear();

	std::fstream fin(mFolderPath + aGraphName + ".bytes", std::ios_base::in | std::ios_base::binary);

	if (!fin.is_open())
	{
		return;
	}

	size_t pinSize;
	fin.read(reinterpret_cast<char*>(&pinSize), static_cast<std::streamsize>(sizeof(size_t)));

	size_t numNodes;
	fin.read(reinterpret_cast<char*>(&numNodes), static_cast<std::streamsize>(sizeof(size_t)));
	std::vector<ByteNode> nodes;
	nodes.resize(numNodes);
	fin.read(reinterpret_cast<char*>(nodes.data()), static_cast<std::streamsize>(sizeof(ByteNode) * numNodes));

	size_t numPins;
	fin.read(reinterpret_cast<char*>(&numPins), static_cast<std::streamsize>(sizeof(size_t)));
	std::vector<BytePin> bytePins;
	bytePins.resize(numPins);
	fin.read(reinterpret_cast<char*>(bytePins.data()), static_cast<std::streamsize>(sizeof(BytePin) * numPins));

	size_t numLinks;
	fin.read(reinterpret_cast<char*>(&numLinks), static_cast<std::streamsize>(sizeof(size_t)));
	std::vector<Link> links;
	links.resize(numLinks);
	fin.read(reinterpret_cast<char*>(links.data()), static_cast<std::streamsize>(sizeof(Link) * numLinks));

	fin.read(reinterpret_cast<char*>(&mCurrentId), static_cast<std::streamsize>(sizeof(int)));
	
	for (int i = 0; i < nodes.size(); ++i)
	{
		Node node;

		node.SetName(nodes[i].name);
		node.SetCategory(nodes[i].category);
		node.SetId(nodes[i].id);
		node.SetType(nodes[i].type);

		Node* newNode = NodeRegistry::CreateNode(node, nullptr);

		std::vector<Pin*> pins;
		for (int j = 0; j < bytePins.size(); ++j)
		{
			if (bytePins[j].nodeId == node.GetId())
			{
				Pin* pin = new Pin(newNode, bytePins[j].id, bytePins[j].text, bytePins[j].type, bytePins[j].direction);
				pins.push_back(pin);
			}
		}

		for (Pin* pin : pins)
		{
			switch (pin->type)
			{
			case PinType::Bool:
			{
				bool b;
				fin.read(reinterpret_cast<char*>(&b), static_cast<std::streamsize>(sizeof(bool)));
				pin->data = b;
				break;
			}
			case PinType::Int:
			{
				int n;
				fin.read(reinterpret_cast<char*>(&n), static_cast<std::streamsize>(sizeof(int)));
				pin->data = n;
				break;
			}
			case PinType::Float:
			{
				float f;
				fin.read(reinterpret_cast<char*>(&f), static_cast<std::streamsize>(sizeof(float)));
				pin->data = f;
				break;
			}
			case PinType::String:
			{
				char buf[256];
				fin.read(reinterpret_cast<char*>(&buf), static_cast<std::streamsize>(256));
				std::string string(buf);
				pin->data = string;
				break;
			}
			default:
				break;
			}
		}

		newNode->SetGraph(graph);
		newNode->SetPins(pins);
		graph->AddNode(newNode);
	}

	for (Link& link : links)
	{
		for (auto& node : graph->GetNodes())
		{
			for (auto& pin : node->GetPins())
			{
				if (link.endPin == pin->id)
				{
					link.endNode = node;
					continue;
				}
				if (link.startPin == pin->id)
				{
					link.startNode = node;
					continue;
				}
			}
		}

		graph->AddLink(link);
	}

	fin.close();
}
