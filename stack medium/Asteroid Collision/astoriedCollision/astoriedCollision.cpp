#include <bits/stdc++.h>
using namespace std;

vector<int> asteroidCollision(int arr[], int len) 
{
    stack<int> s;

    for (int i = 0; i < len; i++) 
    {
        int curr = arr[i];

        while (true) 
        {
            // Push if: stack empty, curr is right-moving, or no collision (same direction)
            if (s.empty() || curr > 0 || s.top() < 0) {
                s.push(curr);
                break;
            }

            // Collision: stack top is right-moving, curr is left-moving
            int top = s.top();
            int topSize = top; // Top is positive
            int currSize = -curr; // Curr is negative

            if (topSize < currSize) {
                s.pop(); // Curr destroys top
                if (s.empty()) {
                    s.push(curr);
                    break;
                }
                continue; // Check further collisions
            }
            else if (topSize == currSize) {
                s.pop(); // Both destroyed
                break;
            }
            else {
                break; // Curr destroyed
            }
        }
    }

    // Convert stack to vector in correct order
    vector<int> result(s.size());
    int index = s.size() - 1;
    while (!s.empty()) {
        result[index--] = s.top();
        s.pop();
    }

    return result;
}

// Example usage
void printVector(const vector<int>& vec) {
    for (int x : vec) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int arr[10]{ -3,-4,-2,2,-8,7,4,-10,-10 };
    vector<int> result1 = asteroidCollision(arr, 9);

    printVector(result1);
    //int arr1[] = { 5, 10, -5 };
    //vector<int> result1 = asteroidCollision(arr1, 3);
    //printVector(result1); // Output: 5 10

    //int arr2[] = { 8, -8 };
    //vector<int> result2 = asteroidCollision(arr2, 2);
    //printVector(result2); // Output: (empty)

    //int arr3[] = { 10, 2, -5 };
    //vector<int> result3 = asteroidCollision(arr3, 3);
    //printVector(result3); // Output: 10

    return 0;
}