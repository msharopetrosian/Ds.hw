#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Rule.h"


std::vector<std::string> topo_sort(const std::string& target, const RuleMap& rules);

static time_t get_mtime(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) return -1;
    return st.st_mtime;
}

bool needs_rebuild(const std::string& target, const std::vector<std::string>& deps) {
    time_t target_mtime = get_mtime(target);
    if (target_mtime == -1) return true;

    for (const auto& dep : deps) {
        time_t dep_mtime = get_mtime(dep);
        if (dep_mtime != -1 && dep_mtime > target_mtime) return true;
    }
    return false;
}

static int run_command(const std::string& command) {
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Error: fork() failed\n";
        return -1;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);

        std::cerr << "Error: execl() failed\n";
        std::exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    return -1;
}

void build(const std::string& target, const RuleMap& rules) {
    std::vector<std::string> order = topo_sort(target, rules);

    for (const auto& node : order) {
        auto it = rules.find(node);
        if (it == rules.end()) {
            if (get_mtime(node) == -1) {
                std::cerr << "Error: no rule to make target '" << node << "'\n";
                std::exit(1);
            }
            continue;
        }

        const Rule& rule = it->second;

        // Phony targets always rebuild; skip mtime check
        if (!rule.is_phony && !needs_rebuild(rule.target, rule.deps)) {
            std::cout << "Up to date: " << rule.target << "\n";
            continue;
        }

        if (rule.commands.empty()) {
            std::cout << "No command for: " << rule.target << "\n";
            continue;
        }

        for (const auto& cmd : rule.commands) {
            std::cout << cmd << "\n";
            int ret = run_command(cmd);
            if (ret != 0) {
                std::cerr << "Error: command failed for target '"
                          << rule.target << "'\n";
                std::exit(ret);
            }
        }
    }
}
