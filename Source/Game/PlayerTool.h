#pragma once
#include "Tool.hpp"

class PlayerTool :
    public Tool
{
public:
    PlayerTool(const char* aConfigPath, GlobalServiceProvider* aGPC);

    void Update();
};

