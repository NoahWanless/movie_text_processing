#ifndef MATRIX_H
#define MATRIX_H
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

#include <random>
using namespace std;

//-----------MATRIX CLASS--------------
/*
Matrix class, made up of a vector of vector's of flaots, with several operations defined that will be needed in the algorithim

Citations:
This website was used for the random float generator that randomized entires in the weights:
https://cplusplus.com/reference/random/uniform_real_distribution/
*/
//------------------------------------
class Matrix{
    public:
        vector<vector<float> > matrix;
        //this is the constructor for a randomized matrix for the rows and columns that are passed in
        //matrix filled with random numbers
        Matrix(int numOfrows, int numOfcolumns){
            //srand(time(0));
            //uniform_int_distribution<int> dist(-5,5);
            for(int i = 0; i < numOfrows; i++){ // for every desired row
                vector<float> newRow; //create a vector that will be the new row
                for(int k = 0; k < numOfcolumns; k++){ //then for the desired num of columns in that row
                    if(rand()%2 == 0){ //50/50 shot of it being a negative or positive number
                        random_device rd;
                        uniform_real_distribution<float> dist(-1,1); //makes it a random float between -1 and 1
                        newRow.push_back(dist(rd));  
                    } else{
                        random_device rd;
                        uniform_real_distribution<float> dist(-1,1);//makes it a random float between -1 and 1
                        newRow.push_back(dist(rd));  //pushs the random entire to the new row
                    }
                } 
                matrix.push_back(newRow); //pushs the new row to the matrix, repeate with all desired rows until done
            }
        }
        //constructor that makes a matrix of a certain size filled only with one number that is pasted in
        Matrix(int numOfrows, int numOfcolumns, int num1){
            for(int i = 0; i < numOfrows; i++){ // for every desired row
                vector<float> newRow; //create a vector that will be the new row
                for(int k = 0; k < numOfcolumns; k++){ //then for the desired num of columns in that row
                    newRow.push_back(num1);
                } 
                matrix.push_back(newRow); //pushs the new row to the matrix, repeate with all desired rows until done
            }
        }
        //constructor with a already complete matrix that you want copied in
        Matrix(vector<vector<float> >& mat){ 
            for(int i = 0; i < mat.size(); i++){
                vector<float> newRow;
                for(int k = 0; k < mat[i].size(); k++){
                    newRow.push_back(mat[i][k]);
                }
                matrix.push_back(newRow);
            }
        }
        
        //matrix multaplication overload
        vector<float> operator*(vector<float>& featureVector){
            vector<float> output; //output vector 
            for(int i = 0; i < matrix.size(); i ++){ //for every row of the matrix
                float weightedSum = 0; //start of weighted sum
                for(int k = 0; k < matrix[i].size(); k ++){ //for every entry in each row
                    weightedSum = weightedSum + (featureVector[k] * matrix[i][k]); //muplitpies its value by the value of the feature vector and adds to weighted sum 
                }
                output.push_back(weightedSum); //then pushs that weighted sum to the output vector
            }
            return output; //returns output
        }
        //matrix addition overload
        Matrix operator+(Matrix& otherM){  
            vector<vector<float> > newMat; //makes a temp matrix
            for(int i = 0; i < otherM.matrix.size(); i++ ){ //its entires are the same as the matrix's to start
                vector<float> newRow;
                for(int j = 0; j < otherM.matrix[0].size(); j++){
                    newRow.push_back(otherM.matrix[i][j] + matrix[i][j]); //makes its entires the sum of the others 
                }
                newMat.push_back(newRow);
            }
            return Matrix(newMat);//returns it as a matrix object
        }
        
        //returns the desired column vecotr 
    vector<float> getColumnvec(int p){ //p is what coloumn you want 
        vector<float> col;
        for(int i = 0; i < matrix.size(); i++){
            col.push_back(matrix[i][p]);
        }
        return col;
    }
    

}; 

#endif 