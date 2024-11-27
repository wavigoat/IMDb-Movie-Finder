#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "nodes.cpp"
using namespace std;

//merge sort

//quick sort

//maxheap

//parse ratings, title, and genre data

//menu for search

vector<string> splitByComma(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;

    // Use getline with ',' as the delimiter to split by commas
    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

int main() {
    vector<HeapNode> heap;
    string tconst;
    string titleType;
    string title;
    int year;
    vector<string> genre;
    float rating;
    int numVotes;
    string directors;

    ifstream file("../imdb_data.tsv");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }
    string line;
    getline(file, line);

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, '\t')) {
            stringstream ss(line);
            string genreString;

            getline(ss, tconst, '\t');
            getline(ss, titleType, '\t');

            getline(ss, title, '\t');
            ss >> year;
            ss.ignore();               // Ignore the tab character after year
            getline(ss, genreString, '\t');
            genre = splitByComma(genreString);
            ss >> rating;
            ss.ignore();
            getline(ss, directors, '\t');
        }
        /**
        //code to check if the information is correct
         cout << title << " ";
        for (int i =0; i<genre.size(); i++){
            cout << genre[i] << " ";
        }
        cout << rating << " ";
        cout << endl;**/
        heap.push_back(HeapNode(title, genre, rating));
        /**string testing = heap[heap.size()-1].getTitle();
        cout << testing << endl;
         **/
    }
    file.close();
    return 0;
}