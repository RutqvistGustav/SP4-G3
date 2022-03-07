#pragma once
#include "UpdateContext.h"

class GlobalServiceProvider;
class NodeGraph;
struct ByteNode;
struct BytePin;

class NodeGraphManager
{
public:
	~NodeGraphManager();

	static NodeGraphManager* Get();
	
	void Init(GlobalServiceProvider* aGsp);
	void Update(const UpdateContext& aUpdateContext);

	void AddGraph(NodeGraph* aGraph);

	NodeGraph* LoadGraph(const std::string& aGraphName);
	NodeGraph* GetGraph(const std::string& aGraphName);
	void IncrementId();

	void SaveGraph(NodeGraph* aGraph);
	void RemoveGraph(NodeGraph* aGraph);
	void RemoveGraph(const std::string& aGraph);

	inline const int GetId() { return mCurrentId; }

	void SetGraphLoaded(const bool aValue);
	inline const bool IsGraphLoaded() { return mGraphLoaded; }
	inline GlobalServiceProvider* GetGSP() { return mGSP; }

private:
	void LoadGraphs();

	void ConvertNodesToBytes(NodeGraph* aGraph, std::vector<ByteNode>& aByteNodes, std::vector<BytePin>& aBytePins);
	void Serialize(NodeGraph* aGraph);
	void Deserialize(const std::string& aFileName);

	const std::string mFolderPath = "NodeEditor/";
	std::vector<NodeGraph*> mGraphs;
	int mCurrentId;
	bool mGraphLoaded;

	GlobalServiceProvider* mGSP;

	static NodeGraphManager* ourInstance;
	NodeGraphManager();
};