#pragma once
#include "Node.h"
class NodeCompareBool :
    public Node
{
public:
    NodeCompareBool();
    NodeCompareBool(const int aId, NodeGraph* aGraph);
    NodeCompareBool(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

