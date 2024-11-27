#include "merge_sort.h"

void merge(std::vector<HeapNode>& heap, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<HeapNode> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = heap[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = heap[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].getRating() > R[j].getRating() ||
            (L[i].getRating() == R[j].getRating() && L[i].getNumVotes() > R[j].getNumVotes())) {
            heap[k] = L[i];
            i++;
            } else {
                heap[k] = R[j];
                j++;
            }
        k++;
    }

    while (i < n1) {
        heap[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        heap[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<HeapNode>& heap, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(heap, left, mid);
        mergeSort(heap, mid + 1, right);

        merge(heap, left, mid, right);
    }
}
