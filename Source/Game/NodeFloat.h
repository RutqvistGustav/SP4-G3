#pragma once
#include "Node.h"
class NodeFloat :
    public Node
{
public:
    NodeFloat();
    NodeFloat(const int aId, NodeGraph* aGraph);
    NodeFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

