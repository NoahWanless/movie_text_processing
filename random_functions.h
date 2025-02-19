#ifndef RANDOM_FUNCTIONS_H
#define RANDOM_FUNCTIONS_H
#include <iostream> 
#include <cmath>    
#include <ctime>    
#include <cstdlib>  
#include <string>   
#include <cctype>   
#include <stdio.h>  
#include <stdlib.h> 
#include <fstream> 
#include <iomanip>   
#include <vector> 
#include <initializer_list> 
#include <algorithm> 
#include <typeinfo> //stuff for polymosrishm and checking what derivated class a object is 

using namespace std;
/*
Sources:
https://towardsdatascience.com/derivative-of-the-sigmoid-function-536880cf918e
used for deravation of the sigmoid function into the simplified version that we use 
along with the sigmoid function itself
*/
// const e to be in sigmoid function
const float e = 2.7182818284590452353602874713526624977572470936999595749; //const e
const float eplsion = pow(10,-20); //tiny number eplsion to avoid NANA
//sigmod funciton but for vectors
//takes in a vector and applies the sigmoid function to each entry, returns a new vector
vector<float> sigmoidVectorversion(vector<float>& vec){
    vector<float> returnVec; //return vector 
    for(int i = 0; i < vec.size(); i++){ //goes through every item of the vec and pushes it through the sigmoid function and gives it to the return vec
        float num = (1/(1+pow(e,-vec[i]))) + eplsion; //puts the value of the vec at i through sigmoid
        if(isnan(num)){
            num = 0;
        }
        returnVec.push_back(num); //pushs the number to the new vector 
    }
    return returnVec; //returns return vector
}
//regular sigmoid function
float sigmoid(float& j ){
    float num = 1/(1+pow(e,-j)) + eplsion;
    if(isnan(num)){ //checks for NAN
        num = 0;
    }
    return (num);
}
//derivative of sigmoid
float sigmoidDer(float& j){ 
    return sigmoid(j) * (1 - sigmoid(j));

}

//loss function to be used in learning, takes in the label, and predicted label, along with what position in the vecotr it wants to take from
//are returns the lose
//This formula was taken for the book: Artificial Intelligence: A Modern Approach 3rd Edition by Stuart Russell
float findLoss(int position, vector<float>& label, vector<float>& predicted){ 
    return (pow((label[position] - predicted[position] + eplsion),1));
}


//dot product definition
float operator*(vector<float> vec1, vector<float> vec2){
    float sum = 0; //defines sum
    for(int i = 0; i< vec1.size(); i ++){ //goes through each entire of vector, and calcuates the weighted sum of all its entire
        sum = sum + vec1[i]*vec2[i];
    }
    return sum; //returns sum
}
//multiplication by scaler definition
vector<float> operator*(vector<float> vec1, float scaler){
    vector<float> newVec;
    for(int i = 0; i < vec1.size(); i++){ //multiplies each entire in the vector based in by a scaler
        newVec.push_back(vec1[i]*scaler); 
    }
    return newVec;
}

//vector addition definition
vector<float> operator+(vector<float>& vec1, vector<float>& vec2){
    vector <float> sumVec;
    for(int i = 0; i< vec1.size(); i ++){
        sumVec.push_back(vec1[i]+vec2[i]); //makes a new vec and adds to it the sum of two entires of the two vectors based in
    }
    return sumVec;
}
//vector subtraction definition
vector<float> operator-(vector<float>& vec1, vector<float>& vec2){
    vector <float> sumVec;
    for(int i = 0; i< vec1.size(); i ++){ 
        sumVec.push_back(vec1[i]-vec2[i]);//makes a new vec and adds to it the subtraction of two entires of the two vectors based in
    }
    return sumVec;
}


//finds lose but as a vector 
vector<float> findLossvecotr(vector<float>& label, vector<float>& predicted){ 
    return (label - predicted); //same as other loss funciton but for whole vector
}


//relu activation function
float relu(float num){
    if(num < 0){ //if less then 0, return the number
        return 0;
    } else{
        return num; //else not
    }
}
//derivative of relu
float reluD(float num){
    if(num > 0){
        return 1;//if greater then 0, return the 1
    } else{
        return 0;//else not. return 0
    }
}
//derivative of relu as a vector
vector<float> reluDvector(vector<float> num3){ 
    vector<float> new1; //does same calcuation but for each entire in the vector
    for(int i = 0; i < num3.size(); i++){
        if(num3[i] > 0){
            new1.push_back(1);
        } else{
            new1.push_back(0);
        }
    }
    return new1; //returns vector 
    
}
//relu activation function but does it for a whole vector and not just the single value
vector <float> reluvector(vector<float> num){
    vector<float> num2;
    for(int i = 0; i < num.size(); i++){ //same as relu, but for a whole vector
        if(num[i] < 0){
            num2.push_back(0);
        } else{
            num2.push_back(num[i]);
        }
    }
    return num2;
    
}
//this function fits a vector to the size that is passed in, only using entries from the vector itself
vector<int> fitDatatoAverage(vector<int> vec, int size){
    if(vec.size() == size){//if it fits the size, returns it unchanged
        return vec;
    } else if(vec.size() < size){ //if it is less then the needed size
        int siz = (size - vec.size()); //determines how many spaces it has to fill
        for(int i = 0; i < siz; i++){ //then pushs entires back till it fits the size 
            vec.push_back(vec[i]);
        }
    } else{//otherwise it has spaces to fill
        int siz = (vec.size() - size);//determines how many spaces it has to remove 
        for(int i = 0; i < (siz); i++){ //and pops back until it fits the size
            vec.pop_back();
        }
    }
    return vec;
}


#endif