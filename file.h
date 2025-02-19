#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "review.h"

using namespace std;

// declerations
vector<int> getData(string filePath, map<string, int> vocabMap);
map<string, int> createMap();
vector<int> mapData(vector<string> parsedFile, map<string, int> vocabMap);
vector<string> parseFileContents(string fileContents);
string cleanFileContents(string fileContents);
string getFileContents(string filePath);
string getFile(int num, string dir);
string getPosTrainFile();
string getNegTrainFile();
vector<Review> getPosTrainData(map<string, int> vocabMap);
vector<Review> getNegTrainData(map<string, int> vocabMap);



//https://www.tensorflow.org/tutorials/keras/text_classification
//the text files were gotten from this website here ^ along with the vocab text file



// getData function
// processes a specific file to a certain map
// gives back the data of the file after processed
vector<int> getData(string filePath, map<string, int> vocabMap) {

    // get the text of the review
    string review = getFileContents(filePath);

    // clean review
    string cleanedReview = cleanFileContents(review);

    // parse review into a vector of each individual word
    vector<string> parsedReview = parseFileContents(cleanedReview);

    // map words to numbers
    vector<int> data = mapData(parsedReview, vocabMap);

    // returns back data of file
    return data;
}


// createMap function
// creates a map from strings to integers of the imdb vocab in the review
// integers needed for model
map<string, int> createMap() {

    // get vocab file
    fstream vocabFile("./aclImdb/imdb.vocab", ios::in);
    vector<string> vocabList; // list of vocab

    // Used maps to assign words, all the vocab in the movie reviews, to arbitrary numbers (line numbers of the vocab list)

    // https://en.cppreference.com/w/cpp/container/map
    // https://cplusplus.com/reference/map/map/
    map<string, int> vocabMap;


    // get all words into a list (vector)
    while (!vocabFile.eof()) {
        string curWord;
        vocabFile >> curWord; // take in next word
        vocabList.push_back(curWord); // add to list
    }

    // close file
    vocabFile.close();

    // map vocab words to nums
    // does by line number 
    for (int i = 0; i < vocabList.size(); i++) {
        vocabMap[ vocabList[i] ] = (i + 1); // from above references
    }

    // return map
    return vocabMap;
}

// mapData function
// takes in a list of words (strings already cleaned, etc...) and maps to a list of integers from given map
// returns back the mapped list of integers
vector<int> mapData(vector<string> parsedFile, map<string, int> vocabMap) {
    vector<int> mappedFile;

    // go through all words
    for (int i = 0; i < parsedFile.size(); i++) {
        // assure word is in the map, otherwise skips
        if (vocabMap.find( parsedFile[i] ) != vocabMap.end()) {
            mappedFile.push_back( vocabMap[ parsedFile[i] ] ); // add mapped int to list
        }
    }

    // return mappedFile
    return mappedFile;
}

// parseFileContents function
// takes in a reviews contents as a string (already cleaned) and parses into a list (vector) of words (strings)
// returns list of words
vector<string> parseFileContents(string fileContents) {
    vector<string> parsedFile;

    string word; 

    // go thorugh all chars of a string (review/file contents)
    for (int i = 0; i < fileContents.size(); i++) {
        if (fileContents[i] != ' ') { // checks for end of word
            word += fileContents[i]; // adds current
        } else if (fileContents[i+1] == ' ') { } //skips to next word, aka skip extra spaces in place from cleaning
        else {
            parsedFile.push_back(word); // add word to list
            word = ""; // reset 
        }
    }

    // return parsedFile
    return parsedFile;
}


// cleanFileContents function
// takes in a review (string), removes all unnecessary info
string cleanFileContents(string fileContents) {

    // remove <br /> , found in numerous of the reviews and doesn't have relevance
    while (fileContents.find("<br />") != string::npos) {
        int pos = fileContents.find("<br />");
        fileContents.replace(pos, 6, " ");
    }

    // remove non letter characters
    // note that only letters are needed, 
    // special chars like ' or - aren't needed as vocab list includes most counterparts without them
    for (int i = 0; i < fileContents.size(); i++) {

        if (fileContents[i] >= 65 && fileContents[i] <= 90) { // check upercase
            fileContents[i] += 32; // change upper to lowercase for mapping later
        } 
        else if (fileContents[i] >= 97 && fileContents[i] <= 122) {} // check lowercase
        else { // remove unwanted characters
            fileContents.replace(i, 1, " "); // replaces with a space, accounted for in parsing
        }
    }

    // return cleaned contents
    return fileContents;
}

// getFileContents
// takes in a filePath (provided by other functions) and gets that reviews contents
// returns back those contents
string getFileContents(string filePath) {
    // open file
    fstream file(filePath, ios::in);

    // get contents
    string fileContents;
    getline(file, fileContents); // the whole review is found on the first line

    // close file
    file.close();

    // return contents
    return fileContents;
}

// getFile function
// this is specialized for how the review file names are formated   ex: 806_10.txt
// note that the 806, is the file number which is provided, while the 10 is arbitary for us, is the rating of review
// looks in a provided directory (aka get a positive review in the training dir)
// find correct file name
// returns back the full directory of that file
string getFile(int num, string dir) {

    string fileName;

    fstream posFile;

    // find right file name 
    // possible endings are from 1-10
    // other parts are fixed, the file num, "_", ".txt"
    for (int i = 1; i <= 10; i++) {
        // fileName to be tested
        fileName = to_string(num) + '_' + to_string(i) + ".txt";
        
        // try to open with name
        posFile.open(dir + fileName);

        // check for correct file name
        if (!posFile.fail()) {
            // cout << "file " << num << " opened with " << i << endl; // debugging
            break; // leave loop when found
        }
    }

    // return complete path with found file name
    return dir + fileName;
}


// getPosTrainFile function
// keeps track of how many files have been gone through, has directory of files
// returns back the directory of file
string getPosTrainFile() {
    // how many files have been gone through for the posTraining files
    static int posTrainNum = 0;

    int curNum = posTrainNum;
    posTrainNum++;
    string dir = "./aclImdb/train/pos/";

    // gets file's correct name and returns whole filePath
    return getFile(curNum, dir);
}

// getNegTrainFile function
// same as above but for negative training files
string getNegTrainFile() {
    static int negTrainNum = 0;

    int curNum = negTrainNum;
    negTrainNum++;
    string dir = "./aclImdb/train/neg/";
    return getFile(negTrainNum, dir);
}

// getPosTrainData function
// gets all of the the positive training data into a vector of reviews
// reviews are simple the list of integers that are the data, as well as the classification if it is positive or negative.
// reviews objects are easier to deal with for the model
// takes in a map of the vocab, processes all desired review traning files(max should be 12500 files/12499 num on the files ) 
// takes processed files, makes review objects, classifed 
// 

//IMPORTANT NOTE ON THESE TWO FUNCTIONS:
// if you want to change how many files they pull from pos or neg from to train with(or test with), change the value that i must be less then
// as marked below
vector<Review> getPosTrainData(map<string, int> vocabMap) {

    vector<Review> posTrainData;

    // go thorugh all desired training files
    // i, can go up to 12500(12499), change depending on how many files are wanting to be grabbed
    for (int i = 0; i < 12; i++) { //!CHANGE THIS VALUE TO CHANGE NUMBER OF POS EXAMPLES TO BE USED
        // get next file
        string path = getPosTrainFile();

        // process that file
        vector <int> d = getData(path, vocabMap);

        // fit data to desired size for model
        d = fitDatatoAverage(d,323); //323 because thats how big our input matirx is

        // push data along with classification onto list of reviews
        posTrainData.push_back(Review(d, 1) ); // 1 for pos classification (or true), would be 0 (or false) for neg
        if(i % 100 == 0){
            cout << "Got file #" << i << endl; // used for keeping track of progress
        }
        
    }

    // return list of all reviews
    cout << "Got all positive training data" << endl << endl;
    return posTrainData;
}

// getNegTrainData function
// same as above but for neg training files
vector<Review> getNegTrainData(map<string, int> vocabMap) {

    vector<Review> negTrainData;

    for (int i = 0; i < 12; i++) { //!CHANGE THIS VALUE TO CHANGE NUMBER OF NEG EXAMPLES TO BE USED
        string path = getNegTrainFile();
        vector <int> d = getData(path, vocabMap);

        //
        d = fitDatatoAverage(d,323);  //323 because thats how big our input matirx is
        negTrainData.push_back(Review( d, 0) );
        if(i % 100 == 0){
            cout << "Got file #" << i << endl;
        }
    }

    cout << "Got all negative training data" << endl << endl;
    return negTrainData;
}



#endif