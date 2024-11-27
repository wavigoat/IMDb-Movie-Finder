#include <iostream>
#include <vector>

#ifndef IMDB_MOVIE_FINDER_NODES_H
#define IMDB_MOVIE_FINDER_NODES_H
using namespace std;
class HeapNode{
private:
    string title;
    float rating;
    vector<string> genre;
public:
    HeapNode(string, vector<string>, float);
};

HeapNode::HeapNode(string newTitle, vector<string> newGenres, float newRating) {
    title = newTitle;
    genre = newGenres;
    rating = newRating;
}

#endif //IMDB_MOVIE_FINDER_NODES_H
