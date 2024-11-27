#include "insertion_sort.h"

void insertionSort(std::vector<HeapNode>& heap) {
    int n = heap.size();
    for (int i = 1; i < n; i++) {
        HeapNode key = heap[i];
        int j = i - 1;

        // Move elements that are greater than key to one position ahead
        while (j >= 0 && (heap[j].getRating() < key.getRating() ||
                          (heap[j].getRating() == key.getRating() && heap[j].getNumVotes() < key.getNumVotes()))) {
            heap[j + 1] = heap[j];
            j--;
                          }
        heap[j + 1] = key;
    }
}
