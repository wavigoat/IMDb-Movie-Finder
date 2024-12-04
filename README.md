# IMDb Movie Finder

## Overview

The **IMDb Movie Finder** is a C++ project designed to help users search for movies based on specific criteria such as genres, minimum ratings, and the number of votes. This program aims to solve the problem of finding and filtering movies from a vast database using various attributes such as genre, director, and rating. With thousands of movies in the IMDb dataset, users may struggle to efficiently search for movies based on their preferences. The project uses various sorting algorithms, including Heap Sort, Merge Sort, Shell Sort, and Insertion Sort, to sort and display movie data efficiently. It also leverages object-oriented programming principles with custom classes like `HeapNode` to represent movie records.

---

### Input Instructions
1. Enter up to two genres to filter movies (or press Enter to skip).
2. Specify the minimum number of votes (default: 100,000).
3. Specify the minimum rating (default: 7.5).
4. Choose between:
   - **Top Films**: Displays the highest-rated movies that match the criteria.
   - **Random Recommendations**: Displays random movies that meet the criteria.
  
- To avoid highly obscure films, keeping your minimum rating filter above ~50,000 or ~100,000 is recommended. Filtering in the range of ~500,000 will ensure only well-known films are chosen.
- For the broadest selection of movies, keep your selection at one genre. For more specialized options, choosing 2 genres will heavily filter the amount of movies that fit the criteria.
- Selecting the top films option will commonly return the same few highly renowned films. The random recommendation option can help expand one's taste by exposing them to similiar films.

---

## Features

- **Interactive CLI**: Users can input up to two genres, a minimum rating, and a minimum number of votes to filter movies.
- **Movie Sorting**: Multiple sorting algorithms are implemented to compare their performance:
  - Heap Sort
  - Merge Sort
  - Shell Sort
  - Insertion Sort
- **Custom Comparison**: Movies are sorted by:
  - Ratings (descending)
  - Number of votes as a tiebreaker (descending)
- **Random Recommendations**: Provides random movie recommendations that meet user-defined criteria.
- **Performance Metrics**: Displays the execution time for each sorting algorithm.

---

## Code Structure

### Files
- **`main.cpp`**: Handles the user interface and integrates sorting algorithms.
- **`nodes.cpp`**: Defines the `HeapNode` class to represent movie records with attributes such as title, genres, rating, number of votes, and directors.
- **`merge_sort.cpp`**: Implements Merge Sort for sorting movie records.
- **`shell_sort.cpp`**: Implements Shell Sort for sorting movie records.
- **`insertion_sort.cpp`**: Implements Insertion Sort for sorting movie records.
- **`heap_sort.cpp`**: Implements Heap Sort for sorting movie records.
- **`imdb_data.tsv`**: Dataset file containing IMDb movie data in a tab-separated format (not included in this repository).

### Classes and Functions
- **`HeapNode`**:
  - Represents a single movie record.
  - Includes attributes: `title`, `genre`, `rating`, `numVotes`, and `directors`.
  - Provides getters for all attributes.
- Sorting functions:
  - `mergeSort`: Implements Merge Sort with `merge` helper function.
  - `shellsort`: Implements Shell Sort.
  - `insertionSort`: Implements Insertion Sort.
  - `heapSort`: Implements Heap Sort with `heapify` helper function.

---

## Dataset Format

The program expects a tab-separated file (`imdb_data.tsv`) with the following columns:
1. `tconst`: Unique identifier for the movie
2. `titleType`: Type of content (e.g., movie, short)
3. `primaryTitle`: Movie title
4. `startYear`: Release year
5. `genres`: Comma-separated list of genres
6. `averageRating`: IMDb rating
7. `numVotes`: Number of votes
8. `directors`: Directors of the movie

---

## Performance Metrics

The program calculates and displays the time taken by each sorting algorithm to sort the dataset. Example output:
```
Heap Sort Time: 0.002 seconds
Insertion Sort Time: 0.015 seconds
Merge Sort Time: 0.008 seconds
Shell Sort Time: 0.010 seconds
```

---
