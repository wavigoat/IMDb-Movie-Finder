#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>
#include "algorithms/nodes.cpp"
#include "algorithms/heap_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/merge_sort.h"
#include "algorithms/shell_sort.h"

using namespace std;

// Convert a string to lowercase
// This function makes the comparison case-insensitive
string toLower(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to split strings by commas
// Used for splitting genre strings in the movie data
vector<string> splitByComma(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

// List of all possible genres for validation
// This is used to ensure user input is valid
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

// Check if the given genre is valid
// Verifies if the input matches a genre from the predefined list
bool viable_genre(const string& input) {
    bool result = false;
    string test = toLower(input);
    vector<string> all_genres = list_of_genres();
    if (find(all_genres.begin(), all_genres.end(), test) != all_genres.end()) {
        result = true;
    }
    return result;
}

// Print all available genres to the user
// Helps the user to understand valid options for genres
void print_genres_available() {
    vector<string> output = list_of_genres();
    for (int i=0; i<output.size(); i++) {
        cout << "     " << output[i] << endl;
    }
}

int main() {
    cout << "Welcome to the IMDb Movie Finder. Please follow the prompts for a list of movie that match your criteria." << endl;
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
                // Inform the user if the genre is not valid and display available options
                cout << "The genre inputted is not available, please enter one of the following:" << endl;
                print_genres_available();
            }
        }

        // Input minimum number of votes and validate input
        while (true) {
            string tempNumVotes;
            cout << "Enter the minimum number of ratings:";
            getline(cin, tempNumVotes);
            if (tempNumVotes.empty()) {
                // Default minimum votes if user provides no input
                cout << "The minimum number of rating has been defaulted to 100,000." << endl;
                minNumVotes = 100000;
                break;
            }
            try {
                minNumVotes = stoi(tempNumVotes);
            } catch (const invalid_argument& e) {
                // Handle invalid non-numeric input
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

        // Input minimum rating and validate input
        float minRating;
        cout << "Enter a decimal minimum rating between 0.0 and 10.0:";

        while (true) {
            string tempMinRating;
            getline(cin, tempMinRating);
            if (tempMinRating.empty()) {
                // Default minimum rating if user provides no input
                cout << "The minimum number of rating has been defaulted to 7.5" << endl;
                minRating = 7.5;
                break;
            }
            try {
                minRating = stof(tempMinRating);
            } catch (const invalid_argument& e) {
                // Handle invalid non-numeric input
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

        // Open the IMDb data file
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
            string choice;
            cout << "\nWould you like the top films or random recommendations? (Enter 'T' for top films, 'R' for random recommendations):";
            getline(cin, choice);
            choice = toLower(choice);

            if (choice == "t" || choice.empty()) {
                if (choice.empty()) {
                    cout << endl;
                    cout << "The choice is defaulted to top films" << endl;
                }
                // Sort the films and display the top 5
                if (heap.empty()) {
                    // Handle case where no movies match the criteria
                    cout << "\nSorry, there are not any movies that match this criteria. PLease use different criteria next time." << endl;
                }
                else {

                    cout << "\nPlease be patient while we generate your list of movies :)" << endl;
                    vector<HeapNode> heapCopy1 = heap;
                    vector<HeapNode> heapCopy2 = heap;
                    vector<HeapNode> heapCopy3 = heap;

                    // Measure time taken for heap sort
                    auto startHeapSort = chrono::high_resolution_clock::now();
                    heapSort(heap);
                    auto endHeapSort = chrono::high_resolution_clock::now();
                    chrono::duration<double> heapSortDuration = endHeapSort-startHeapSort;

                    // Measure time taken for insertion sort
                    auto startInsertionSort = chrono::high_resolution_clock::now();
                    insertionSort(heapCopy1);
                    auto endInsertionSort = chrono::high_resolution_clock::now();
                    chrono::duration<double> insertionSortDuration = endInsertionSort-startInsertionSort;

                    // Measure time taken for merge sort
                    auto startMergeSort = chrono::high_resolution_clock::now();
                    mergeSort(heapCopy2, 0, heapCopy2.size() - 1);
                    auto endMergeSort = chrono::high_resolution_clock::now();
                    chrono::duration<double> mergeSortDuration = endMergeSort-startMergeSort;

                    // Measure time taken for shell sort
                    auto startShellSort = chrono::high_resolution_clock::now();
                    shellsort(heapCopy3);
                    auto endShellSort = chrono::high_resolution_clock::now();
                    chrono::duration<double> shellSortDuration = endShellSort-startShellSort;

                    // Output sorting times for comparison
                    cout << "\nHeap Sort Time: " << heapSortDuration.count() << " seconds" << endl;
                    cout << "Insertion Sort Time: " << insertionSortDuration.count() << " seconds" << endl;
                    cout << "Merge Sort Time: " << mergeSortDuration.count() << " seconds" << endl;
                    cout << "Shell Sort Time: " << shellSortDuration.count() << " seconds" << endl;

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

                    // Output the 5 highest-rated movies that match the filter using shell sort
                    cout << "\nTop 5 highest-rated movies in given genre(s) with at least " << minNumVotes
                         << " ratings (Shell Sort):"
                         << endl;
                    for (int i = heapCopy3.size() - 1; i >= max(0, static_cast<int>(heapCopy3.size()) - 5); i--) {
                        cout << "Title: " << heapCopy3[i].getTitle() << ", Director(s): " << heapCopy3[i].getDirectors()
                             << ", Rating: "
                             << heapCopy3[i].getRating() << ", Number of Ratings: " << heapCopy3[i].getNumVotes() << endl;
                    }
                }
                break;
            } else if (choice == "r") {
                if (heap.empty()) {
                    // Handle case where no movies match the criteria
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

                    cout << "\nHere are 5 random movies that match the criteria:" << endl;
                    for (int i = 0; i < 5 && i < filteredMovies.size(); i++) {
                        cout << "Title: " << filteredMovies[i].getTitle() << ", Director(s): "
                             << filteredMovies[i].getDirectors() << ", Rating: " << filteredMovies[i].getRating()
                             << ", Number of Ratings: " << filteredMovies[i].getNumVotes() << endl;
                    }
                }
                break;
            }
            else {
                // Handle invalid choice input
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
