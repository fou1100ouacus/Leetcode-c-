// vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bits/stdc++.h>
using namespace std;
#include<vector>
int main()
{


}

vector<int> resultsArray(vector<int> nums, int k)
{

	int n = nums.size();
	vector<int> ans(n - k + 1);
	for (int i = 0; i < n - k + 1; i++)
	{
		int counter = 1;
		for (int j = 1+i; j < k+i; j++)
		{
			if (nums[j]==nums[j-1]+1)
			{
				counter++;
			}
			ans[i] = counter >= k ? nums[i + k - 1] : -1;
		}
		return ans;

	}







}


vector<int> resultsArrayOptimized(vector<int> nums, int k)
{

	int n = nums.size();
	vector<int> ans(n - k + 1);
	int counter = 1;

	for (int i = 0; i < k ; i++)
	{

		if (nums[i] == nums[i - 1] + 1)
		{
			counter++;
		}
		else
		{
			counter = 1;
		}
		ans[i] = counter == k ? nums[ k - 1] : -1;


		for (int i = k; i < n; i++)
		{
			if (nums[i] == nums[i - 1] + 1)
			{
				counter++;
			}
			else
			{
				counter = 1;
			}
			ans[i-k+1] = counter >= k ? nums[i] : -1;

		}

		return ans;

	}







}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
