#include "merge_sort.h"

// Merges two subarrays of 'heap' into a sorted array
void merge(std::vector<HeapNode>& heap, int left, int mid, int right) {
    // Calculate the sizes of the two subarrays
    int n1 = mid - left + 1;  // Size of the left subarray
    int n2 = right - mid;     // Size of the right subarray

    // Create temporary vectors to hold the subarrays
    std::vector<HeapNode> L(n1), R(n2);

    // Copy data into the left and right subarrays
    for (int i = 0; i < n1; i++)
        L[i] = heap[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = heap[mid + 1 + j];

    // Initialize indices for left (i), right (j), and merged array (k)
    int i = 0, j = 0, k = left;

    // Merge the two subarrays back into 'heap'
    while (i < n1 && j < n2) {
        // Compare elements by rating, and by number of votes if ratings are equal
        if (L[i].getRating() > R[j].getRating() ||
            (L[i].getRating() == R[j].getRating() && L[i].getNumVotes() > R[j].getNumVotes())) {
            heap[k] = L[i];  // Choose the left element if it is greater
            i++;
        } else {
            heap[k] = R[j];  // Choose the right element otherwise
            j++;
        }
        k++;
    }

    // Copy any remaining elements from the left subarray
    while (i < n1) {
        heap[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements from the right subarray
    while (j < n2) {
        heap[k] = R[j];
        j++;
        k++;
    }
}

// Implements merge sort algorithm on 'heap' within the range [left, right]
void mergeSort(std::vector<HeapNode>& heap, int left, int right) {
    // Base case: if there is more than one element, continue dividing
    if (left < right) {
        // Calculate the middle point to split the array
        int mid = left + (right - left) / 2;

        // Recursively sort the left half
        mergeSort(heap, left, mid);

        // Recursively sort the right half
        mergeSort(heap, mid + 1, right);

        // Merge the sorted halves
        merge(heap, left, mid, right);
    }
}
