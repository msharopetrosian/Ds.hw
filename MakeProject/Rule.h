#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Rule {
    std::string              target;
    std::vector<std::string> deps;
    std::vector<std::string> commands;  // multiple commands per rule
    bool                     is_phony = false;
};

using RuleMap = std::unordered_map<std::string, Rule>;
