#include "insertion_sort.h"

// Implementation of Insertion Sort for sorting HeapNode objects
void insertionSort(std::vector<HeapNode>& heap) {
    long n = heap.size();  // Get the size of the heap

    // Iterate through the array starting from the second element
    for (long i = 1; i < n; i++) {
        HeapNode key = heap[i];  // Store the current element as the key
        long j = i - 1;

        // Shift elements of the sorted portion that are less than the key
        while (j >= 0 &&
               (heap[j].getRating() < key.getRating() ||  // Compare ratings
               (heap[j].getRating() == key.getRating() && heap[j].getNumVotes() < key.getNumVotes()))) {  // Break ties using number of votes
            heap[j + 1] = heap[j];  // Shift element to the right
            j--;
               }

        // Place the key in its correct position in the sorted portion
        heap[j + 1] = key;
    }
}
