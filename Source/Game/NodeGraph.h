#pragma once
#include "UpdateContext.h"

class Node;
class NodeStart;
struct Pin;

struct Link
{
	int id = 0;
	int startPin = 0;
	int endPin = 0;
	Node* startNode = nullptr;
	Node* endNode = nullptr;
};

class NodeGraph
{
public:
	NodeGraph();
	NodeGraph(const std::string& aName);
	~NodeGraph();

	void Init();
	void Update(const UpdateContext& aContext);
	void Clear();

	void RunStart(Node* aNode);
	void RunStartNodes();

	inline const std::vector<Node*> GetNodes() { return mNodes; }
	//inline const std::vector<Node*> GetStartNodes() { return mStartNodes; }
	inline const std::string& GetName() { return mName; }
	const std::vector<Pin*> GetAllPins();
	std::vector<Link>& GetLinks();

	void SetName(const std::string& aName);

	void AddNode(Node* aNode);
	void RemoveNode(const int aId);
	void AddLink(Link& aLink);
	void RemoveLink(const int aId);

	inline const CommonUtilities::Input* GetInput() { return mInput; }

private:
	int RunNode(Node* aNode);

	std::vector<Node*> mNodes;
	std::vector<Link> mLinks;
	std::vector<std::pair<bool, Node*>> mStartNodes;
	std::string mName;

	CommonUtilities::Input* mInput;

	bool mRunning = false;
};

