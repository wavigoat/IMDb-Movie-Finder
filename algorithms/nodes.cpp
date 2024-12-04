#include <iostream>
#include <vector>

#ifndef IMDB_MOVIE_FINDER_NODES_H
#define IMDB_MOVIE_FINDER_NODES_H

using namespace std;

// Class representing a movie node for the heap
class HeapNode {
private:
    string title;                // Movie title
    vector<string> genre;        // List of genres for the movie
    float rating;                // Movie rating
    int numVotes;                // Number of votes the movie received
    string directors;            // Directors of the movie

public:
    // Default constructor
    HeapNode() {
        // Initializes an empty movie node with default values
        title = "";
        genre = {};
        rating = 0.0;
        numVotes = 0;
        directors = "";
    }

    // Parameterized constructor
    HeapNode(string newTitle, vector<string> newGenres, float newRating, int newNumVotes, string newDirectors) {
        // Initializes a movie node with specific values
        title = newTitle;
        genre = newGenres;
        rating = newRating;
        numVotes = newNumVotes;
        directors = newDirectors;
    }

    // Getters to access private attributes of the class

    // Returns the title of the movie
    string getTitle() {
        return title;
    }

    // Returns the genres of the movie as a vector of strings
    vector<string> getGenre() {
        return genre;
    }

    // Returns the rating of the movie
    float getRating() {
        return rating;
    }

    // Returns the number of votes the movie received
    int getNumVotes() {
        return numVotes;
    }

    // Returns the directors of the movie
    string getDirectors() {
        return directors;
    }
};

#endif // IMDB_MOVIE_FINDER_NODES_H
