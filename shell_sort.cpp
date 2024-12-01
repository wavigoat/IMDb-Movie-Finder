#include "shell_sort.h"

void shellsort(vector<HeapNode>& heap) {
    long n = heap.size();

    for (long gap = n / 2; gap > 0; gap /= 2) {

        for (long i = gap; i < n; i++) {
            HeapNode temp = heap[i];
            float tempRating = temp.getRating();

            long j;
            for (j=i; j >= gap && heap[j - gap].getRating() > tempRating; j-=gap) {
                heap[j] = heap[j - gap];
            }
            heap[j] = temp;
        }
    }
}
