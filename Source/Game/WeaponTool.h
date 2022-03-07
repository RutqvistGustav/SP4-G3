#pragma once
#include "Tool.hpp"

class WeaponTool :
    public Tool
{
public:
    WeaponTool(const char* aConfigPath, GlobalServiceProvider* aGPC);

    void Update();
};

