#pragma once
#include "Tool.hpp"

class EnemyTool :
    public Tool
{
public:
    EnemyTool(const char* aConfigPath, GlobalServiceProvider* aGPC);

    void Update();
};

