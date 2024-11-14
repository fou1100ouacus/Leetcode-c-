// ReverseInt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bits/stdc++.h>
class Solution {
public:
    int reverse(int x)
    {
        int ans = 0;
        while (x != 0) {
            int digit = x % 10;

            if ((ans > INT_MAX / 10) || (ans < INT_MIN / 10)) {
                return 0;
            }

            ans = ans * 10 + digit;
            x = x / 10;
        }
        return ans;

    }
};
int main()
{
    std::cout << "Hello World!\n";
}

