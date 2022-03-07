#pragma once
#include "Node.h"

constexpr int LOOP_PIN_ID = 1;

class NodeStart :
    public Node
{
public:
    NodeStart();
    NodeStart(const int aId, NodeGraph* aGraph);
    NodeStart(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

