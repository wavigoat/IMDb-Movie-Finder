#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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

vector<string> list_of_genres () {
    vector<string> result;
    result.push_back("action");
    result.push_back("adventure");
    result.push_back("animation");
    result.push_back("biography");
    result.push_back("comedy");
    result.push_back("crime");
    result.push_back("documentary");
    result.push_back("drama");
    result.push_back("family");
    result.push_back("fantasy");
    result.push_back("film-noir");
    result.push_back("game-show");
    result.push_back("history");
    result.push_back("horror");
    result.push_back("music");
    result.push_back("musical");
    result.push_back("mystery");
    result.push_back("news");
    result.push_back("reality-TV");
    result.push_back("romance");
    result.push_back("sci-fi");
    result.push_back("sport");
    result.push_back("talk-show");
    result.push_back("thriller");
    result.push_back("war");
    result.push_back("western");

    return result;

}

bool viable_genre(string input) {
    bool result = false;
    string test = toLower(input);
    vector<string> all_genres = list_of_genres();
    if (find(all_genres.begin(), all_genres.end(), input) != all_genres.end()) {
        result = true;
    }
    return result;
}

void print_genres_available() {
    vector<string> output = list_of_genres();
    for (int i=0; i<output.size(); i++) {
        cout << "     " << output[i] << endl;
    }
}

int main() {

    while(true) {
        vector<HeapNode> heap;
        string tconst, titleType, title, directors, line;
        int year, numVotes;
        vector<string> genre;
        float rating;

        // Input up to two genres and minimum number of ratings
        vector<string> targetGenres;
        int minNumVotes;
        cout << "Enter up to two genres to filter by (press enter without input to stop): " << endl;
        int i = 1;
        while(i<=2) {
            string genreInput;
            cout << "Genre " << (i) << ":";
            getline(cin, genreInput);
            if (genreInput.empty()) {
                break;
            }
            if (viable_genre(genreInput)) {
                targetGenres.push_back(toLower(genreInput));
                i++;
            }
            else {
                cout << "The genre inputted is not available, please enter one of the following:" << endl;
                print_genres_available();
            }
        }

        while (true) {
            string tempNumVotes;
            cout << "Enter the minimum number of ratings:";
            getline(cin, tempNumVotes);
            if (tempNumVotes.empty()) {
                cout << "The minimum number of rating has been defaulted to 0." << endl;
                minNumVotes = 0;
                break;
            }
            try {
                minNumVotes = stoi(tempNumVotes);
            } catch (const invalid_argument& e) {
                cout << "Enter an integer greater than or equal to 0" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "Enter an integer greater than or equal to 0" << endl;
                continue;
            }
            if (minNumVotes<0) {
                cout << "Enter an integer greater than or equal to 0" << endl;
                continue;
            }
            else {
                break;
            }
        }

        float minRating;
        cout << "Enter a decimal minimum rating between 0.0 and 10.0:";

        while (true) {
            string tempMinRating;
            getline(cin, tempMinRating);
            if (tempMinRating.empty()) {
                cout << "The minimum number of rating has been defaulted to 0.0" << endl;
                minRating = 0.0;
                break;
            }
            try {
                minRating = stof(tempMinRating);
            } catch (const invalid_argument& e) {
                cout << "Enter a decimal minimum rating between 0.0 and 10.0: " << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "Enter a decimal minimum rating between 0.0 and 10.0: " << endl;
                continue;
            }
            if (minRating<0.0 || minRating>10.0) {
                cout << "Enter a decimal minimum rating between 0.0 and 10.0: " << endl;
                continue;
            }
            else {
                break;
            }
        }



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
            } catch (const invalid_argument &) {
                continue;  // Skip if rating is missing or non-numeric
            }

            ss >> numVotes;
            ss.ignore(); // get to directors
            ss.ignore();
            ss.ignore();
            getline(ss, directors, '\t');

            // Check if the movie matches all of the specified genres and minimum number of ratings
            bool genreMatch = true;
            for (const auto &targetGenre: targetGenres) {
                if (find_if(genre.begin(), genre.end(), [&](const string &g) { return toLower(g) == targetGenre; }) ==
                    genre.end()) {
                    genreMatch = false;
                    break;
                }
            }

            if (genreMatch && numVotes >= minNumVotes && rating>=minRating) {
                heap.push_back(HeapNode(title, genre, rating, numVotes, directors));
            }
        }
        file.close();


        // Ask the user if they want the top films or random recommendations
        while (true) {
            char choice;
            cout
                    << "\nWould you like the top films or random recommendations? (Enter 'T' for top films, 'R' for random recommendations): ";
            cin >> choice;
            cin.ignore();
            choice = tolower(choice);

            if (choice == 't') {

                // Sort the films and display the top 5
                if (heap.empty()) {
                    cout << "\nSorry, there are not any movies that match this criteria. PLease use different criteria next time." << endl;
                }
                else {
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
                    cout << "\nHeap Sort Time: " << heapSortDuration.count() << " seconds" << endl;
                    cout << "Insertion Sort Time: " << insertionSortDuration.count() << " seconds" << endl;
                    cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds" << endl;

                    // Output the 5 highest-rated movies that match the filter using heap sort
                    cout << "\nTop 5 highest-rated movies in given genre(s) with at least " << minNumVotes
                         << " ratings (Heap Sort):"
                         << endl;
                    for (int i = heap.size() - 1; i >= max(0, static_cast<int>(heap.size()) - 5); i--) {
                        cout << "Title: " << heap[i].getTitle() << ", Director(s): " << heap[i].getDirectors()
                             << ", Rating: "
                             << heap[i].getRating() << ", Number of Ratings: " << heap[i].getNumVotes() << endl;
                    }

                    // Output the 5 highest-rated movies that match the filter using insertion sort
                    cout << "\nTop 5 highest-rated movies in given genre(s) with at least " << minNumVotes
                         << " ratings (Insertion Sort):" << endl;
                    for (int i = 0; i < 5 && i < heapCopy1.size(); i++) {
                        cout << "Title: " << heapCopy1[i].getTitle() << ", Director(s): " << heapCopy1[i].getDirectors()
                             << ", Rating: " << heapCopy1[i].getRating() << ", Number of Ratings: "
                             << heapCopy1[i].getNumVotes() << endl;
                    }

                    // Output the 5 highest-rated movies that match the filter using merge sort
                    cout << "\nTop 5 highest-rated movies in given genre(s) with at least " << minNumVotes
                         << " ratings (Merge Sort):"
                         << endl;
                    for (int i = 0; i < 5 && i < heapCopy2.size(); i++) {
                        cout << "Title: " << heapCopy2[i].getTitle() << ", Director(s): " << heapCopy2[i].getDirectors()
                             << ", Rating: " << heapCopy2[i].getRating() << ", Number of Ratings: "
                             << heapCopy2[i].getNumVotes() << endl;
                    }
                }
                break;
            } else if (choice == 'r') {
                if (heap.empty()) {
                    cout << "\nSorry, there are not any movies that match this criteria. PLease use different criteria next time." << endl;
                }
                else {

                    // Filter movies that match the minimum rating criteria
                    vector<HeapNode> filteredMovies;
                    for (auto &movie: heap) {
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
                        cout << "Title: " << filteredMovies[i].getTitle() << ", Director(s): "
                             << filteredMovies[i].getDirectors() << ", Rating: " << filteredMovies[i].getRating()
                             << ", Number of Ratings: " << filteredMovies[i].getNumVotes() << endl;
                    }
                }
                break;
            } else {
                cout << "That is not one of the options, please choose either 'T' or 'R'." << endl;
                continue;
            }
        }
        char to_continue;
        cout << "\nWould you like to continue browsing for movies? (Enter 'Y' for yes):";

         cin >> to_continue;
         cin.ignore();
        to_continue = tolower(to_continue);
        if (to_continue == 'y') {
            cout << "\n";
            continue;
        }
        else {
            cout << "\nThank you for using our IMDb Movie Finder!";
            break;
        }
    }

    return 0;
}
