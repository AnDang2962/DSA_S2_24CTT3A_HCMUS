#include"Header.h";

using namespace std;

void Swap(int arr[], int low, int high) {
	int temp = arr[low];
	arr[low] = arr[high];
	arr[high] = temp;
}

int FindMin(int arr[], int low, int n) {
	int min = low;
	for (int i = low + 1; i < n; i++) {
		if (arr[i] < arr[min]) {
			min = i;
		}
	}
	return min;
}


int Partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1; 
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) { 
			i++;
			Swap(arr, i, j);
		}
	}
	Swap(arr, i + 1, high);
	return i + 1;
}



void Merge(int arr[], int low, int mid, int high) {
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int* left = new int[n1];
	int* right = new int[n2];

	for (int i = 0; i < n1; i++)
		left[i] = arr[low + i];
	for (int j = 0; j < n2; j++)
		right[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = low;

	while (i < n1 && j < n2) {
		if (left[i] <= right[j]) {
			arr[k] = left[i];
			i++;
		}
		else {
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = left[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = right[j];
		j++;
		k++;
	}

	delete[] left;
	delete[] right;
}

void Heapify(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		Heapify(arr, n, largest);
	}
}

void CountingSort(int arr[], int n, int exp) {
	int* output = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		int digit = (arr[i] / exp) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
}