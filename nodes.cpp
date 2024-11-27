#include <iostream>
#include <vector>

#ifndef IMDB_MOVIE_FINDER_NODES_H
#define IMDB_MOVIE_FINDER_NODES_H

using namespace std;

class HeapNode {
private:
    string title;
    vector<string> genre;
    float rating;
    int numVotes;
    string directors;

public:
    // Default constructor
    HeapNode() {
        title = "";
        genre = {};
        rating = 0.0;
        numVotes = 0;
        directors = "";
    }

    // Parameterized constructor
    HeapNode(string newTitle, vector<string> newGenres, float newRating, int newNumVotes, string newDirectors) {
        title = newTitle;
        genre = newGenres;
        rating = newRating;
        numVotes = newNumVotes;
        directors = newDirectors;
    }

    // Getters
    string getTitle() {
        return title;
    }

    vector<string> getGenre() {
        return genre;
    }

    float getRating() {
        return rating;
    }

    int getNumVotes() {
        return numVotes;
    }

    string getDirectors() {
        return directors;
    }
};

#endif // IMDB_MOVIE_FINDER_NODES_H
