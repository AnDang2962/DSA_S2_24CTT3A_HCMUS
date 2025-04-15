#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include <cstring> 

using namespace std;


//Khối khai báo hàm để thực hiện 7 thuật toán sắp xếp
void Swap(int arr[], int l, int r);
void BubbleSort(int arr[], int n);
int FindMin(int arr[], int low, int n);
void SelectionSort(int arr[], int n);
int Partition(int arr[], int low, int high);
void QuickSort(int arr[], int low, int high);
void Merge(int arr[], int low, int mid, int high);
void MergeSort(int arr[], int low, int high);
void InsertionSort(int a[], int n);
void Heapify(int arr[], int n, int i);
void HeapSort(int arr[], int n);
void CountingSort(int arr[], int n, int exp);
void RadixSort(int arr[], int n);
void Sort(int arr[], int n, const string& sortType);







