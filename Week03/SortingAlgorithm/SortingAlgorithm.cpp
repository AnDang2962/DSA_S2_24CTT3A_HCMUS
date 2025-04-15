#include"Header.h";

// 7 thuật toán sắp xếp

//Bubble sort algorithm
void BubbleSort(int arr[], int n) {
	int temp;
	for (int i = 1; i < n; i++) {
		bool swapped = false;
		for (int j = n - 1; j >= i; j--) {
			if (arr[j] < arr[j - 1]) {
				Swap(arr, j - 1, j);
				swapped = true;
			}
		}
		if (swapped == false) break;
	}
}

//Selection sort algorithm
void SelectionSort(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		int min = FindMin(arr, i, n);
		Swap(arr, i, min);
	}
}



void QuickSort(int arr[], int low, int high) {
	while (low < high) {
		int pi = Partition(arr, low, high);

		if (pi - low < high - pi) {
			QuickSort(arr, low, pi - 1);
			low = pi + 1;
		}
		else {
			QuickSort(arr, pi + 1, high);
			high = pi - 1;
		}
	}
}


//Merge sort algorithm:
void MergeSort(int arr[], int low, int high) {
	if (low < high) {
		int mid = low + (high - low)/2;
		MergeSort(arr, low, mid);
		MergeSort(arr, mid + 1, high);
		Merge(arr, low, mid, high);
	}
}

//Insertion Sort algorithm:
void InsertionSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
}

//Heap sort algorithm:
void HeapSort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(arr, n, i);

	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		Heapify(arr, i, 0);
	}
}

// Radix sort algorithm:
void RadixSort(int arr[], int n) {
	int maxNum = *max_element(arr, arr + n);

	for (int exp = 1; maxNum / exp > 0; exp *= 10)
		CountingSort(arr, n, exp);
}

void Sort(int arr[], int n, const string& sortType) {
	if (sortType == "bubble-sort") BubbleSort(arr, n);
	else if (sortType == "selection-sort") SelectionSort(arr, n);
	else if (sortType == "quick-sort") QuickSort(arr, 0, n - 1);
	else if (sortType == "merge-sort") MergeSort(arr, 0, n - 1);
	else if (sortType == "insertion-sort") InsertionSort(arr, n);
	else if (sortType == "heap-sort") HeapSort(arr, n);
	else if (sortType == "radix-sort") RadixSort(arr, n);
	else {
		cout << "Unsupported sort type: " << sortType << endl;
		exit(1);
	}
}