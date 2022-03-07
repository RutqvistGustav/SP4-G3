#pragma once
#include "Node.h"

class ConsolePrint :
    public Node
{
public:
    ConsolePrint();
    ConsolePrint(const int aId, NodeGraph* aGraph);
    ConsolePrint(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

