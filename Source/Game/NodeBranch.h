#pragma once
#include "Node.h"
class NodeBranch :
    public Node
{
public:
    NodeBranch();
    NodeBranch(const int aId, NodeGraph* aGraph);
    NodeBranch(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

