#include "heap_sort.h"

void heapify(std::vector<HeapNode>& heap, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    // Check if left child is larger than root
    if (left < n && (heap[left].getRating() > heap[largest].getRating() ||
                     (heap[left].getRating() == heap[largest].getRating() && heap[left].getNumVotes() > heap[largest].getNumVotes()))) {
        largest = left;
                     }

    // Check if right child is larger than largest so far
    if (right < n && (heap[right].getRating() > heap[largest].getRating() ||
                      (heap[right].getRating() == heap[largest].getRating() && heap[right].getNumVotes() > heap[largest].getNumVotes()))) {
        largest = right;
                      }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapify(heap, n, largest);
    }
}

void heapSort(std::vector<HeapNode>& heap) {
    int n = heap.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(heap[0], heap[i]);

        // Call max heapify on the reduced heap
        heapify(heap, i, 0);
    }
}
