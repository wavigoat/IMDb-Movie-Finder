#include <iostream>
#include <vector>

#ifndef IMDB_MOVIE_FINDER_NODES_H
#define IMDB_MOVIE_FINDER_NODES_H
using namespace std;
class HeapNode{
private:
    string title;
    vector<string> genre;
    float rating;
public:
    HeapNode(string newTitle, vector<string> newGenres, float newRating) {
        title = newTitle;
        genre = newGenres;
        rating = newRating;
    }
    string getTitle(){
        return title;
    }
    vector<string> getGenre(){
        return genre;
    }
    float getRating(){
        return rating;
    }
};

#endif //IMDB_MOVIE_FINDER_NODES_H
