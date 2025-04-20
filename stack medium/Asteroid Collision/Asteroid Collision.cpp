#include<iostream>
#include<cassert>
#include <bits/stdc++.h>
using namespace std;


// simple trick to avoid re-changing the class
typedef int type;

class Stack {
private:
	int size{ };
	int top{ };
	type* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new type[size];
	}

	~Stack() {
		delete[] array;
	}

	void push(type x) {
		assert(!isFull());
		array[++top] = x;
	}

	type pop() {
		assert(!isEmpty());
		return array[top--];
	}

	type peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display_reversed() {
		for (int i = 0; i <= top; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};
//
//void asteroidCollision(int arr[], int len) 
//{
//	Stack s(len);
//	s.push(arr[0]);
//	for (int  i = 0; i < len; i++)
//	{
//		
//		bool isnegative = false;
//		if (arr[i+1]<0)
//		{
//			isnegative = true;
//		}
//		if (s.peek()>arr[i+1] && isnegative && s.peek() < abs(arr[i+1]))// remove first ele
//		{
//			// remove from array by doing next step to next index;
//			s.pop();
//			s.push(arr[i + 1]);
//		}
//		else
//		{
//			//i++ by loop 
//		}
//
//	}
//	
//}

std::vector<int> asteroidCollision(int arr[], int len) {
	stack<int> s;

	for (int i = 0; i < len; i++) {
		int curr = arr[i];

		while (true) {
			// Push if: stack is empty, or no collision (both same direction or top is left-moving)
			if (s.empty() || curr > 0 || s.top() < 0) {
				s.push(curr);
				break;
			}

			// Collision: top is right-moving (positive), curr is left-moving (negative)
			int top = s.top();
			int topSize = top; // Since top is positive
			int currSize = -curr; // Since curr is negative

			if (topSize < currSize) {
				s.pop(); // Current asteroid destroys top
				if (s.empty()) {
					s.push(curr);
					break;
				}
				continue; // Check for more collisions
			}
			else if (topSize == currSize) {
				s.pop(); // Both destroyed
				break;
			}
			else {
				break; // Current asteroid destroyed
			}
		}
	}

	// Convert stack to vector in correct order
	std::vector<int> result(s.size());
	int index = s.size() - 1;
	while (!s.empty()) {
		result[index--] = s.top();
		s.pop();
	}

	return result;
}
int main() {
	int arr[10]{ -3,-4,-2,2,-8,7,4,-10,-10  };
	asteroidCollision(arr, 9);

	// Try also 1, 0, -1, 1  ==> 1

	return 0;
}
