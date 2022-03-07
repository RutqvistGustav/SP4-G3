#pragma once
#include "Node.h"
class NodeBool :
    public Node
{
public:
    NodeBool();
    NodeBool(const int aId, NodeGraph* aGraph);
    NodeBool(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

