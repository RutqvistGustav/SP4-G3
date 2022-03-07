#pragma once
#include "Node.h"

class AdditionFloat :
    public Node
{
public:
    AdditionFloat();
    AdditionFloat(const int aId, NodeGraph* aGraph);
    AdditionFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

