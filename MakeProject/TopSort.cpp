#include <iostream>
#include <cstdlib>
#include "Rule.h"


enum class VisitState { UNVISITED, IN_PROGRESS, DONE };

static void dfs(
    const std::string& node,
    const RuleMap& rules,
    std::unordered_map<std::string, VisitState>& state,
    std::vector<std::string>& order
) {
    auto it = state.find(node);
    if (it != state.end()) {
        if (it->second == VisitState::IN_PROGRESS) {
            std::cerr << "Error: circular dependency at '" << node << "'\n";
            std::exit(1);
        }
        if (it->second == VisitState::DONE) return;
    }

    state[node] = VisitState::IN_PROGRESS;

    auto rule_it = rules.find(node);
    if (rule_it != rules.end()) {
        for (const auto& dep : rule_it->second.deps)
            dfs(dep, rules, state, order);
    }

    state[node] = VisitState::DONE;
    order.push_back(node);
}

std::vector<std::string> topo_sort(const std::string& target, const RuleMap& rules) {
    std::unordered_map<std::string, VisitState> state;
    std::vector<std::string> order;
    dfs(target, rules, state, order);
    return order;
}
