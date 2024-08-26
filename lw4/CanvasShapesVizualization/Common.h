#pragma once
#include "CPoint.h"
#include <string>

std::string GetHexStrFromUint32(uint32_t const& uint32);

uint32_t GetUInt32ColorFromString(std::string const& str);

double GetEdgeLength(CPoint const& p1, CPoint const& p2);