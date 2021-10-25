/*
	Salei, Roya

	Dec 1st, 2020

	CS3310
	Project 2
*/
#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include<string>
#include<math.h>
#include <algorithm> 
#include <cstdlib>

using namespace std;

void swap(int& x, int& y);
void mergeSort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
void display(int arr[], int size);
int select_kth1(int arr[], int low, int high, int key);
int select_kth2(int arr[], int low, int high, int key);
int select_kth3(int arr[], int low, int high, int key);
int select_kth4(int arr[], int low, int high, int key);
//bool select_kth3(int arr[], int low, int high, int key, int& kth_val);
int partition(int arr[], int low, int high, int pivot);
int findMedian(int arr[], int low, int high);
//bool duplicate(int arr[], int size, int element);


int main()
{
	//std::ofstream algo_time("times.csv", std::ios::app);
	int n[] = { 10, 50, 100, 250, 500, 1000 };
	
	double t1 = 0;
	for (int r = 0; r < 1000; r++)
	{
		for (int i = 0; i < 6; i++)
		{
			int size = n[i];
			int* ar1 = new int[size];

			for (int j = 0; j < size; j += 2)
			{
				// fill the array with unique unordered digits
				ar1[j] = j + 1;
				if (size < 100) ar1[j + 1] = 250 - j;
				else ar1[j + 1] = 1500 - j;
			}
			int key = 1; double multiple[4] = { 0.25, 0.5, 0.75, 1 };
			for (int h = 0; h < 4; h++)
			{
				//----------------------------------------------------------
				auto start_kth1 = std::chrono::high_resolution_clock::now();
				//display(ar1, size);
				select_kth1(ar1, 0, size - 1, key);
				auto finish_kth1 = std::chrono::high_resolution_clock::now();
				double t1 = std::chrono::duration_cast<std::chrono::microseconds>
					(finish_kth1 - start_kth1).count();

				//algo_time << t1 << "\n"; 
				cout << t1 << " ";
				//key = floor(size * multiple[i]);


				//----------------------------------------------------------
				auto start_kth2 = std::chrono::high_resolution_clock::now();
				//display(ar1, size);
				select_kth2(ar1, 0, size - 1, key);
				auto finish_kth2 = std::chrono::high_resolution_clock::now();
				double t2 = std::chrono::duration_cast<std::chrono::microseconds>
					(finish_kth2 - start_kth2).count();
				//algo_time << t2 << "\n";
				//key = floor(size * multiple[i]);
				cout << t2 << " ";

				//----------------------------------------------------------
				auto start_kth3 = std::chrono::high_resolution_clock::now();
				//display(ar1, size);
				select_kth3(ar1, 0, size - 1, key);
				auto finish_kth3 = std::chrono::high_resolution_clock::now();
				double t3 = std::chrono::duration_cast<std::chrono::microseconds>(finish_kth3 - start_kth3).count();
				//algo_time << t3 << "\n";
				//key = floor(size * multiple[i]);
				cout << t3 << " ";

				//----------------------------------------------------------
				auto start_kth4 = std::chrono::high_resolution_clock::now();
				//display(ar1, size);
				int k = select_kth4(ar1, 0, size - 1, key);
				auto finish_kth4 = std::chrono::high_resolution_clock::now();
				double t4 = std::chrono::duration_cast<std::chrono::microseconds>(finish_kth4 - start_kth4).count();
				//algo_time << t4 << "\n";
				cout << t4 << " \n";

				key = int(floor(size * multiple[h]));
			}
			//algo_time << "---------------\n";
			//cout << "----------------------round 1-----------------------------" << endl;

			//algo_time.close();
			delete[] ar1;
			ar1 = nullptr;
		}

	}
	
	

	cout << endl;
	return 0;
}

int select_kth1(int arr[], int low, int high, int key)
{
	int size = high - low + 1;
	if (size > 0)
	{
		mergeSort(arr, low, high);
		return arr[key - 1];
	}
	else
		cerr << "Array is empty" << endl;
}

void mergeSort(int arr[], int low, int high)
{
	if (low == high)
		return;
	int mid = floor((low + high) / 2);
	if (low < high)
	{
		int mid = int(floor((low + high) / 2));
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

void merge(int arr[], int low, int mid, int high)
{
	int size = (high - low) + 1;
	int* temp;
	temp = new int[size];

	int i = low, j = mid + 1, k = 0;

	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
		{
			temp[k] = arr[i];
			i++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= mid)
	{
		temp[k] = arr[i];
		k++; i++;
	}
	while (j <= high)
	{
		temp[k] = arr[j];
		k++; j++;
	}

	for (int i = 0; i < size; i++)
	{
		arr[low + i] = temp[i];
	}

	delete[] temp;
	temp = nullptr;
}

void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void display(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int select_kth2(int arr[], int low, int high, int key)
{
	if (key >= 0 && key <= high - low + 1)
	{
		int pivot;
		while (true)
		{
			if (low == high)
				return arr[low];

			pivot = arr[high];
			pivot = partition(arr, low, high, pivot);

			if (key == pivot)
				return arr[key];
			else if (key < pivot)
				high = pivot - 1;
			else
				low = pivot + 1;
		}
	}
	else
		return -1;
}

int partition(int arr[], int low, int high, int pivot)
{
	int size = high - low + 1;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == pivot)
		{
			swap(arr[i], arr[high]);
			break;
		}
	}
	int i = low - 1;
	int j = high + 1;
	while (i < j)
	{
		i++; while (arr[i] < pivot) { i++; }
		j--; while (arr[j] > pivot) { j--; }
		if (i < j) { swap(arr[i], arr[j]); }
	}
	return j;
}

int select_kth3(int arr[], int low, int high, int key)
{
	if (key >= 0 && key <= high - low + 1)
	{
		if (low == high)
			return arr[low];

		int pivot = arr[high];
		pivot = partition(arr, low, high, pivot);

		if (key == pivot)
			return arr[key];
		else if (key < pivot)
			return select_kth3(arr, low, pivot - 1, key);
		else
			return select_kth3(arr, pivot + 1, high, key);
	}
	else
		return -1;
}

int findMedian(int arr[], int low, int high)
{
	int size = high - low + 1;
	sort(&arr[low], &arr[high]);

	return arr[size / 2];
}

int select_kth4(int arr[], int low, int high, int key)
{
	if (key > 0 && key <= high - low + 1)
	{
		int size = high - low + 1;
		int sub_size = (size + 4) / 5;
		int* medians;
		medians = new int[sub_size];
	/*	int temp[5];

		for (int i = low; i < size; i++)
			temp[i] = arr[i];*/

		int j;
		for (j = 0; j < sub_size - 1; j++)
		{
			medians[j] = findMedian(arr, 5 * j + low, 5 * j + low + 4);
		}

		if (size % 5 == 0)
		{
			medians[j] = findMedian(arr, 5 * j + low, 5 * j + low + 4);
			j++;
		}
		else
		{
			medians[j] = findMedian(arr, 5 * j + low, 5 * j + low + (size % 5));
			j++;
		}

		int mm;
		if (j == 1)
			mm = medians[j - 1];
		else
			mm = select_kth4(medians, 0, j - 1, j / 2);


		int p = partition(arr, low, high, mm);
		
		delete[] medians;
		medians = nullptr;

		if (p - low == key - 1)
			return arr[p];
		if (p - low < key - 1)
			return select_kth4(arr, p + 1, high, key - (p + 1) + low);

		return select_kth4(arr, low, p - 1, key);

	}
	else
		return -1;

}

//bool duplicate(int arr[], int size, int element)
//{
//	for (int i = 0; i < size; i++) 
//		if (arr[i] == element)
//			return true;
//	return false;
//}
