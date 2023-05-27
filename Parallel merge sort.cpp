#include <iostream>
#include <omp.h>
using namespace std;
void merge(int arr[], int left, int mid, int right) {
 int n1 = mid - left + 1;
 int n2 = right - mid;
 int L[n1], R[n2];
 for (int i = 0; i < n1; i++) {
 L[i] = arr[left + i];
 }
 for (int i = 0; i < n2; i++) {
 R[i] = arr[mid + 1 + i];
 }
 int i = 0, j = 0, k = left;
 while (i < n1 && j < n2) {
 if (L[i] <= R[j]) {
 arr[k++] = L[i++];
 } else {
 arr[k++] = R[j++];
 }
 }
 while (i < n1) {
 arr[k++] = L[i++];
 }
 while (j < n2) {
 arr[k++] = R[j++];
 }
}
void parallelMergeSort(int arr[], int left, int right) {
 if (left < right) {
 int mid = left + (right - left) / 2;
 #pragma omp parallel sections
 {
 #pragma omp section
 parallelMergeSort(arr, left, mid);
 #pragma omp section
 parallelMergeSort(arr, mid + 1, right);
 }
 merge(arr, left, mid, right);
 }
}
int main() {
 int arr[] = {8, 1, 2, 7, 4, 5};
 int n = sizeof(arr) / sizeof(arr[0]);
 parallelMergeSort(arr, 0, n - 1);
 for (int i = 0; i < n; i++) {
 cout << arr[i] << " ";
 }
 cout << endl;
 return 0;
}