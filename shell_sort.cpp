#include "shell_sort.h"

// Implementation of Shell Sort for sorting HeapNode objects
void shellsort(vector<HeapNode>& heap) {
    long n = heap.size();  // Get the size of the heap

    // Start with a large gap, then reduce it incrementally
    for (long gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for the current gap size
        for (long i = gap; i < n; i++) {
            HeapNode temp = heap[i];  // Store the current element
            float tempRating = temp.getRating();  // Extract the rating for comparison
            int tempNumVotes = temp.getNumVotes();  // Extract the number of votes for tie-breaking

            long j;

            // Compare and shift elements in the gap-sorted subarray
            for (j = i;
                 j >= gap &&
                 (heap[j - gap].getRating() > tempRating ||  // Compare ratings
                 (heap[j - gap].getRating() == tempRating && heap[j - gap].getNumVotes() > tempNumVotes)); // Break ties with number of votes
                 j -= gap) {
                heap[j] = heap[j - gap];  // Shift the larger element up
                 }

            // Place the temporary element in its correct position
            heap[j] = temp;
        }
    }
}
