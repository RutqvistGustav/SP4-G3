#pragma once
#include "Node.h"
class NodeIsGreaterOrEqualInt :
    public Node
{
public:
    NodeIsGreaterOrEqualInt();
    NodeIsGreaterOrEqualInt(const int aId, NodeGraph* aGraph);
    NodeIsGreaterOrEqualInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

