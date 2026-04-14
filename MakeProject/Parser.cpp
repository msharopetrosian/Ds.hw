#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "Rule.h"


static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

static std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string tok;
    while (iss >> tok) tokens.push_back(tok);
    return tokens;
}

std::pair<RuleMap, std::string> parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file '" << filename << "'\n";
        std::exit(1);
    }

    RuleMap     rules;
    std::string first_target;
    std::string current_target;
    std::string line;
    int         line_num = 0;

    while (std::getline(file, line)) {
        ++line_num;

        if (trim(line).empty() || trim(line)[0] == '#') continue;

        if (!line.empty() && line[0] == '\t') {
            if (current_target.empty()) {
                std::cerr << filename << ":" << line_num
                          << ": command without a target\n";
                continue;
            }
            rules[current_target].commands.push_back(trim(line));
            continue;
        }

        size_t colon = line.find(':');
        if (colon == std::string::npos) {
            std::cerr << filename << ":" << line_num
                      << ": ignoring malformed line: " << trim(line) << "\n";
            continue;
        }

        std::string target   = trim(line.substr(0, colon));
        std::string deps_str = trim(line.substr(colon + 1));

        // .PHONY declaration — mark each listed target as phony
        if (target == ".PHONY") {
            for (const auto& t : split(deps_str))
                rules[t].is_phony = true;
            current_target = "";
            continue;
        }

        Rule rule;
        rule.target   = target;
        rule.deps     = split(deps_str);
        rule.commands = {};
        rule.is_phony = rules[target].is_phony; // preserve any prior .PHONY marking

        rules[target]  = rule;
        current_target = target;

        if (first_target.empty())
            first_target = target;
    }

    return {rules, first_target};
}
