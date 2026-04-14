#include <iostream>
#include "Rule.h"


std::pair<RuleMap, std::string> parse(const std::string& filename);
void build(const std::string& target, const RuleMap& rules);

int main(int argc, char* argv[]) {
    std::string makefile = "Makefile";
    std::string target   = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-f") {
            if (i + 1 >= argc) {
                std::cerr << "Error: -f requires a filename argument\n";
                return 1;
            }
            makefile = argv[++i];
        } else {
            target = arg;
        }
    }

    auto [rules, first] = parse(makefile);

    if (rules.empty()) {
        std::cerr << "Error: no rules found in '" << makefile << "'\n";
        return 1;
    }

    if (target.empty())
        target = first;

    if (target.empty()) {
        std::cerr << "Error: no target specified\n";
        return 1;
    }

    std::cout << "Target: " << target << "\n\n";
    build(target, rules);

    return 0;
}
