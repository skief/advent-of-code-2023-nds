#pragma once

#include <vector>
#include <string>
#include <inttypes.h>

std::vector<std::string> split(const std::string& txt, const std::string& delim);
std::vector<int> toIntVec(const std::vector<std::string>& strVec);
std::vector<int64_t> toIntVec64(const std::vector<std::string> &strs);
