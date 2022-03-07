#pragma once
#include "Node.h"
class NodeInt :
    public Node
{
public:
    NodeInt();
    NodeInt(const int aId, NodeGraph* aGraph);
    NodeInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

private:
    void SetData();
    void CreatePins();
    int Run() override;
};

