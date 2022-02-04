#pragma once
#include <Windows.h>
#include <vector>
#include <Psapi.h>

void* PatternScan(void* module, const char* signature);