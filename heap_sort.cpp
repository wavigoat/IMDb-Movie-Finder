#include "heap_sort.h"

// Function to maintain the max-heap property
void heapify(std::vector<HeapNode>& heap, int n, int i) {
    int largest = i;            // Initialize the largest element as the root
    int left = 2 * i + 1;       // Index of the left child
    int right = 2 * i + 2;      // Index of the right child

    // Check if the left child exists and is greater than the current largest
    if (left < n && (heap[left].getRating() > heap[largest].getRating() ||
                     (heap[left].getRating() == heap[largest].getRating() && heap[left].getNumVotes() > heap[largest].getNumVotes()))) {
        largest = left;         // Update largest to left child
                     }

    // Check if the right child exists and is greater than the current largest
    if (right < n && (heap[right].getRating() > heap[largest].getRating() ||
                      (heap[right].getRating() == heap[largest].getRating() && heap[right].getNumVotes() > heap[largest].getNumVotes()))) {
        largest = right;        // Update largest to right child
                      }

    // If the largest is not the root, swap and recursively heapify
    if (largest != i) {
        std::swap(heap[i], heap[largest]); // Swap the root with the largest child
        heapify(heap, n, largest);         // Recursively heapify the affected sub-tree
    }
}

// Main function to perform heap sort
void heapSort(std::vector<HeapNode>& heap) {
    int n = heap.size(); // Get the size of the heap

    // Build a max-heap by rearranging the array
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i); // Heapify each non-leaf node starting from the bottom
    }

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(heap[0], heap[i]); // Move the current root to the end

        // Call heapify on the reduced heap to restore the max-heap property
        heapify(heap, i, 0);
    }
}
