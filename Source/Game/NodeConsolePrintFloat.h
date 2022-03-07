#pragma once
#include "Node.h"

class ConsolePrintFloat :
    public Node
{
public:
    ConsolePrintFloat();
    ConsolePrintFloat(const int aId, NodeGraph* aGraph);
    ConsolePrintFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

    void CreatePins();
    int Run() override;
};

