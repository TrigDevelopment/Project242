#pragma once
#include <random>
#include <vector>
#include <array>
#include <string>

using RandomInt = std::uniform_int_distribution<std::mt19937::result_type>;
using Program = std::vector<char>;
using CRProgram = std::vector<char> const &;
using Arities = std::vector<int> const;
using Names = std::vector<std::string> const;