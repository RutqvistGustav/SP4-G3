#pragma once
#include "Node.h"

namespace CommonUtilities
{
    class InputHandler;
}

class NodeInput :
    public Node
{
public:
    NodeInput();
    NodeInput(const int aId, NodeGraph* aGraph);
    NodeInput(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph);

public:
    void CreatePins();
    int Run() override;

    CommonUtilities::InputHandler* myInput;
};

