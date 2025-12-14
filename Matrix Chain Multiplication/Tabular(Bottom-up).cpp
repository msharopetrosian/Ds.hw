#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int mcmTabulation(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Chain length
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                    + p[i - 1] * p[k] * p[j];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];
}

int main() {
    vector<int> p = { 10, 30, 5, 60 };

    cout << "Minimum multiplications (Bottom-Up): "
        << mcmTabulation(p) << endl;

    return 0;
}
