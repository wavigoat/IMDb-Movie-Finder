#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>
#include "nodes.cpp"
#include "heap_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"

using namespace std;

// Convert a string to lowercase
string toLower(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to split strings by commas
vector<string> splitByComma(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

int main() {
    vector<HeapNode> heap;
    string tconst, titleType, title, directors, line;
    int year, numVotes;
    vector<string> genre;
    float rating;

    // Input up to two genres and minimum number of ratings
    vector<string> targetGenres;
    int minNumVotes;
    cout << "Enter up to two genres to filter by (press enter without input to stop): " << endl;
    for (int i = 0; i < 2; ++i) {
        string genreInput;
        cout << "Genre " << (i + 1) << ": ";
        getline(cin, genreInput);
        if (genreInput.empty()) {
            break;
        }
        targetGenres.push_back(toLower(genreInput));
    }
    cout << "Enter the minimum number of ratings: ";
    cin >> minNumVotes;
    cin.ignore();  // Ignore newline character left in the buffer

    ifstream file("../imdb_data.tsv");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    getline(file, line);  // Skip header line

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string genreString;

        getline(ss, tconst, '\t');
        getline(ss, titleType, '\t');
        getline(ss, title, '\t');
        ss >> year;
        ss.ignore();  // Ignore the tab character after year
        getline(ss, genreString, '\t');
        genre = splitByComma(genreString);

        string ratingStr;
        getline(ss, ratingStr, '\t');

        // Handle missing or invalid rating
        try {
            rating = stof(ratingStr);
            if (rating <= 0) {
                continue;  // Skip if rating is invalid or 0
            }
        } catch (const invalid_argument&) {
            continue;  // Skip if rating is missing or non-numeric
        }

        ss >> numVotes;
        ss.ignore(); // get to directors
        ss.ignore();
        ss.ignore();
        getline(ss, directors, '\t');

        // Check if the movie matches all of the specified genres and minimum number of ratings
        bool genreMatch = true;
        for (const auto& targetGenre : targetGenres) {
            if (find_if(genre.begin(), genre.end(), [&](const string& g) { return toLower(g) == targetGenre; }) == genre.end()) {
                genreMatch = false;
                break;
            }
        }

        if (genreMatch && numVotes >= minNumVotes) {
            heap.push_back(HeapNode(title, genre, rating, numVotes, directors));
        }
    }
    file.close();

    // Ask the user if they want the top films or random recommendations
    char choice;
    cout << "\nWould you like the top films or random recommendations? (Enter 'T' for top films, 'R' for random recommendations): ";
    cin >> choice;
    choice = tolower(choice);

    if (choice == 't') {
        // Sort the films and display the top 5
        vector<HeapNode> heapCopy1 = heap;
        vector<HeapNode> heapCopy2 = heap;

        // Measure time taken for heap sort
        auto startHeapSort = chrono::high_resolution_clock::now();
        heapSort(heap);
        auto endHeapSort = chrono::high_resolution_clock::now();
        chrono::duration<double> heapSortDuration = endHeapSort - startHeapSort;

        // Measure time taken for insertion sort
        auto startInsertionSort = chrono::high_resolution_clock::now();
        insertionSort(heapCopy1);
        auto endInsertionSort = chrono::high_resolution_clock::now();
        chrono::duration<double> insertionSortDuration = endInsertionSort - startInsertionSort;

        // Measure time taken for merge sort
        auto startMergeSort = chrono::high_resolution_clock::now();
        mergeSort(heapCopy2, 0, heapCopy2.size() - 1);
        auto endMergeSort = chrono::high_resolution_clock::now();
        chrono::duration<double> mergeSortDuration = endMergeSort - startMergeSort;

        // Output sorting times
        cout << "Heap Sort Time: " << heapSortDuration.count() << " seconds" << endl;
        cout << "Insertion Sort Time: " << insertionSortDuration.count() << " seconds" << endl;
        cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds" << endl;

        // Output the 5 highest-rated movies that match the filter using heap sort
        cout << "\nTop 5 highest-rated movies in genre(s) with at least " << minNumVotes << " ratings (Heap Sort):" << endl;
        for (int i = heap.size() - 1; i >= max(0, static_cast<int>(heap.size()) - 5); i--) {
            cout << "Title: " << heap[i].getTitle() << ", Director(s): " << heap[i].getDirectors() << ", Rating: " << heap[i].getRating() << ", Number of Ratings: " << heap[i].getNumVotes() << endl;
        }

        // Output the 5 highest-rated movies that match the filter using insertion sort
        cout << "\nTop 5 highest-rated movies in genre(s) with at least " << minNumVotes << " ratings (Insertion Sort):" << endl;
        for (int i = 0; i < 5 && i < heapCopy1.size(); i++) {
            cout << "Title: " << heapCopy1[i].getTitle() << ", Director(s): " << heapCopy1[i].getDirectors() << ", Rating: " << heapCopy1[i].getRating() << ", Number of Ratings: " << heapCopy1[i].getNumVotes() << endl;
        }

        // Output the 5 highest-rated movies that match the filter using merge sort
        cout << "\nTop 5 highest-rated movies in genre(s) with at least " << minNumVotes << " ratings (Merge Sort):" << endl;
        for (int i = 0; i < 5 && i < heapCopy2.size(); i++) {
            cout << "Title: " << heapCopy2[i].getTitle()  << ", Director(s): " << heapCopy2[i].getDirectors() << ", Rating: " << heapCopy2[i].getRating() << ", Number of Ratings: " << heapCopy2[i].getNumVotes() << endl;
        }

    } else if (choice == 'r') {
        // Get the minimum rating for random recommendations
        float minRating;
        cout << "Enter the minimum rating for random recommendations: ";
        cin >> minRating;

        // Filter movies that match the minimum rating criteria
        vector<HeapNode> filteredMovies;
        for (auto& movie : heap) {
            if (movie.getRating() >= minRating) {
                filteredMovies.push_back(movie);
            }
        }

        // Shuffle the filtered movies and display 5 random ones
        random_device rd;
        mt19937 g(rd());
        shuffle(filteredMovies.begin(), filteredMovies.end(), g);

        cout << "\nRandom 5 movies that match the criteria:" << endl;
        for (int i = 0; i < 5 && i < filteredMovies.size(); i++) {
            cout << "Title: " << filteredMovies[i].getTitle() << ", Director(s): " << filteredMovies[i].getDirectors() << ", Rating: " << filteredMovies[i].getRating() << ", Number of Ratings: " << filteredMovies[i].getNumVotes() << endl;
        }
    } else {
        cout << "Invalid choice. Please restart the program and choose either 'T' or 'R'." << endl;
    }

    return 0;
}
