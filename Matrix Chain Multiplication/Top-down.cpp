#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int mcmMemo(int i, int j, const vector<int>& p, vector<vector<int>>& dp) {
    // Base case
    if (i == j)
        return 0;

    // Already computed
    if (dp[i][j] != -1)
        return dp[i][j];

    dp[i][j] = INT_MAX;

    for (int k = i; k < j; k++) {
        int cost = mcmMemo(i, k, p, dp)
                 + mcmMemo(k + 1, j, p, dp)
                 + p[i - 1] * p[k] * p[j];

        dp[i][j] = min(dp[i][j], cost);
    }

    return dp[i][j];
}

int main() {
    vector<int> p = {10, 30, 5, 60};
    int n = p.size() - 1;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    cout << "Minimum multiplications (Top-Down): "
         << mcmMemo(1, n, p, dp) << endl;

    return 0;
}
