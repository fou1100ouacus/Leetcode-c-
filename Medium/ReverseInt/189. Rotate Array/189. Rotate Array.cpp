
#include <bits/stdc++.h>
using namespace std;
void ReadArray(int arr[], int n)
{

	for (int i = 0; i < n; i++)
	{
		//	cout << "enter Element: ";
		cin >> arr[i];

	}
}
void PrintArray(int arr[], int n)
{

	cout << " [ ";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ",";


	}
	cout << "]" << endl;
}
void ReverseArray(int arr[], int n) {

	int start = 0, End = n - 1;

	while (start <= End)
	{// swap
		int Temp = arr[start];
		arr[start] = arr[End];
		arr[End] = Temp;
		start++; End--;


	}
}

void Reverse(vector<int>& nums, int s, int e) {
	while (s < e) 
	{
		swap(nums[s++], nums[e--]);
	}
}

void rotate(vector<int>& nums, int k) {
	int n = nums.size(); // Size of the array
	k = k % n; // Normalize k to be within bounds of the array length
	int rotate = n - k - 1; // Calculate the point to split the array

	// Step 1: Reverse the first part
	Reverse(nums, 0, rotate);

	// Step 2: Reverse the second part
	Reverse(nums, rotate + 1, n - 1);

	// Step 3: Reverse the entire array
	Reverse(nums, 0, n - 1);
}



int main()
{

	int arr[100], n = 7;
	int arr2[100];
	//9 4 5 2 6 7 11
	//4 2  6 9 5 7 11
	ReadArray(arr, n);


	//cout << "Before Reversing" << endl;
	//PrintArray(arr, n);
	//ReverseArray(arr, n);
	//cout << "After Reversing" << endl;
	//PrintArray(arr, n);




}
