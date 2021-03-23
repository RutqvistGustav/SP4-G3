#pragma once

#include "JsonData.h"

class IJsonInitializable
{
public:

	virtual void InitWithJson(const JsonData& someJsonData) = 0;

};