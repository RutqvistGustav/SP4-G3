#include "stdafx.h"
#include "RandomHelper.h"

std::default_random_engine RandomHelper::ourRandomEngine = std::default_random_engine{ std::random_device{}() };