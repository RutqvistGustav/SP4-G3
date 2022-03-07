#pragma once
#include "Node.h"
class NodeAddInt :
    public Node
{
public:
    NodeAddInt();
    NodeAddInt(const int aId, NodeGraph* aGraph);
    NodeAddInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

private:
    void SetData();
    void CreatePins();
    int Run() override;
};

