#include <iostream>
#include <cmath>


int iterative(int x, int n)
{
    int ans = 1;
    for (int i = 0; i < n; i++)    
    {
        ans *= x;
    }
    
    return ans;
}

int recursive(int x, int n)
{
    int ans = 1;
    if (n == 0) ans = 1;
    else ans = x * pow(x, n - 1);

    return ans;
}

int fastexp(int x, int n)      // fast exponentiation
{
    int ans = 1;
    if (n == 0) ans = 1;

    if (n % 2 == 0)
    {
        return ans = pow(x, n / 2) * pow(x, n / 2);  // n is even
    }

    else
    {
        return ans = x * pow(x, (n - 1) / 2) * pow(x, (n - 1) / 2);
    }
}


int main()
{
    int x, n;
    
    std::cout << "x="; std::cin >> x;
    std::cout << "n="; std::cin >> n;

    std::cout << "Iterative solution - " << iterative(x, n) << endl;
    std::cout << "Recursive solution - " << recursive(x, n) << endl;
    std::cout << "O(log n) solution - " << fastexp(x, n) << endl;

}


