#ifndef REVIEW_H
#define REVIEW_H


#include <vector>

using namespace std;


// Review Class
// Acts as a layer to better process reviews for the model
// hold the data of the review (words mapped to numbers in a vector) as well as if it it a positive review or not
// allows access to that information
class Review {
    private:
        bool isPos; // type of review, true if positive
        vector<int> data; // mapped integers of review words

    public:
        // Review constructor
        Review(vector<int> d, bool p) : data(d), isPos(p) {}

        // get reviews data
        vector<int> getData() const {
            return data;
        }

        // get type of review, pos or negative
        bool getType() const {
            return isPos;
        }

};

#endif