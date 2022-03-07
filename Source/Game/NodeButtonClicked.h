#pragma once
#include "Node.h"
class NodeButtonClicked :
    public Node
{
public:
    NodeButtonClicked();
    NodeButtonClicked(const int aId, NodeGraph* aGraph);
    NodeButtonClicked(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

public:
    void CreatePins();
    int Run() override;
};

