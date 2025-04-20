#include"sorts.h"

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
void selectionSort(int arr[], int n) { // поочередно переносим min эл
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}
void insertionSort(int arr[], int n) { // колода карт, сравниваем число с левым и переносим на нужную позицию сдвигая все остальные на 1
	for (int i = 1; i < n; i++) {
		int value = arr[i], position = i;
		while (arr[position - 1] > value && position > 0) {
			arr[position] = arr[position - 1];
			position--;
		}
		arr[position] = value;
	}
}
void shellSort(int arr[], int n) { //insertionSort с уменьшением расстояния
	for (int step = n / 2; step > 0; step /= 2) {
		for (int i = step; i < n; i++) {
			for (int j = i - step; j >= 0 && arr[j] > arr[j + step]; j -= step) {
				swap(arr[j], arr[j + step]);
			}
		}
	}
}
void quickSort(int arr[], int left, int right) {
	if (left >= right) return;
	int pivot = arr[(left + right) / 2], i = left, j = right;
	while (i <= j) {
		for (; arr[i] < pivot; i++);
		for (; arr[j] > pivot; j--);
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	quickSort(arr, left, j);
	quickSort(arr, i, right);
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
