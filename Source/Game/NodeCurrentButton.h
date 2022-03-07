#pragma once
#include "Node.h"
class NodeCurrentButton :
    public Node
{
public:
    NodeCurrentButton();
    NodeCurrentButton(const int aId, NodeGraph* aGraph);
    NodeCurrentButton(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

public:
    void CreatePins();
    int Run() override;

};

