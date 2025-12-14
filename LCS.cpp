#include <iostream>
#include <string>
using namespace std;

int lcs(const string& X, const string& Y, int i, int j) {
    // Base case
    if (i == 0 || j == 0)
        return 0;

    // If last characters match
    if (X[i - 1] == Y[j - 1])
        return 1 + lcs(X, Y, i - 1, j - 1);

    // If last characters do not match
    return max(lcs(X, Y, i - 1, j),
               lcs(X, Y, i, j - 1));
}

int main() {
    string X = "ABCBDAB";
    string Y = "BDCAB";

    cout << "LCS length: "
         << lcs(X, Y, X.size(), Y.size()) << endl;

    return 0;
}
