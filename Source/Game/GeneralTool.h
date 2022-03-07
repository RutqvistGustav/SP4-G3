#pragma once
#include "Tool.hpp"

class GeneralTool :
    public Tool
{
public:
    GeneralTool(GlobalServiceProvider* aGSP);

    void Update();

    inline const bool GetShowCollider() { return myShowColliders; }

private:
    GlobalServiceProvider* myGSP;

    bool myShowColliders;
};

