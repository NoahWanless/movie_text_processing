#ifndef MODEL_H
#define MODEL_H

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
#include "matrix.h"
#include "random_functions.h"

using namespace std;


//-----------MODEL CLASS--------------
/*
Model class, made up of a vector of matrix's which contain the models weights, a vector containing the model info and sizing,
vector of matrix's containing old changes made to the models weights
and several learning constants
as for methods it contains training, predicting, storing the model to a file, and loading that file into a blank model, 
along with constructors for blank models 
Citations:
    Book: The actual algorithim that was used in this model was taken from the following book that Kent let us borrow:
    Artificial Intelligence: A Modern Approach 3rd Edition by Stuart Russell
    Kent, Kent helped with the NAN detection
    
*/
//------------------------------------
class Model{
    private:
        vector<Matrix> layers; //layers is a list of matrixs which hold the weights 
        vector<Matrix> previousChanges;//list of old chnages made in the training process  //~ Not used 
        vector<int> _layerInfo;
        float learningRate = 1;
        float beta1 = 0.9; //~ Not used 
    public:
        //gets a matrix from the list of matrixs
        Matrix getMat(int num){
            return layers[num];
        }
        // adds a layer to the layer vector 
        void addLayer(Matrix& mat){
            layers.push_back(mat);
        }
        //adds info to the layer info vector
        void addInfo(int in){
            _layerInfo.push_back(in);
        }
        //adds a matrix to the change list
        void addChange(Matrix& mat){ //~ Not used 
            previousChanges.push_back(mat);
        }
        //resets and clears the list of weights and replaces it with the list of matrixs passed in
        void resetLayers( vector<Matrix> newLayers){
            layers.clear();
            for(int i = 0; i < newLayers.size(); i ++){ //adds each layer
                addLayer(newLayers[i]);
            }
        }
        //resests the list of previous rate of changes 
        void resetChanges(vector<Matrix> newLayers){ //~ Not used 
            previousChanges.clear(); //clears old list
            for(int i = 0; i < newLayers.size(); i ++){ //adds in the new matrix's
                addChange(newLayers[i]); //adds the change to the change 3D matrix 
            }
        }
        //------------Model Prediction------------
        //passes in the layer info, each entire in the array is a layer, with its value being the number of nodes
        //adds a matrix for each layer of randomized values that gets the layer dimensions from the layer info that is passed in
        //also adds to the lsit of old changes
        Model(int layerInfo[], int numOflayers){
            for(int i = 0; i < numOflayers; i++){ //for the number of layers
                _layerInfo.push_back(layerInfo[i]); //pushs the layer info into the layerInfo vector
                if(i>0){ //if the layer we are working on 
                    //first number is the number of rows, the second is the number of columns 
                    //which for the matrix and vector multicplation to work, the column size needs to match the number of rows of the previous matrix (unless its the first, then square matrix)
                    Matrix mat(layerInfo[i], layerInfo[i - 1]); //makes matrix 
                    this->addLayer(mat);//adds matrix to layers 
                    Matrix mat2(layerInfo[i], layerInfo[i - 1], 0); //makes old chaneg list
                    this->addChange(mat2);//adds change 
                }else{ //if the layer is the first one, it will be sqaure
                    Matrix mat(layerInfo[i], layerInfo[i]); 
                    this->addLayer(mat);//adds layer
                    Matrix mat2(layerInfo[i], layerInfo[i], 0); //makes old chaneg list
                    this->addChange(mat2); //adds change 
                }
            }

        }
        Model(){ //defalut constructor, does nothing but doesnt need to, cause in this cause a model is loaded in by a file

        }
        //------------Model Prediction------------
        vector<float> predict(vector<float> featureVector){
            for(int i = 0; i < layers.size(); i ++){ //goes through each layer
                featureVector = layers[i] * featureVector; //calcuates the dot product between the feature vector and the matrix of weights for that layer
                featureVector = sigmoidVectorversion(featureVector); //passes the feature vector through the sigmod function
            }
            return featureVector; //returns the output vector
        }
        //------------Store Model------------
        //passes in a file path and stores all the model information into that file to be saved
        void storeModel(string path){
            ofstream store;
            store.open(path);
            for(int i = 0; i < _layerInfo.size(); i++){ //goes through all the layer info
                store << _layerInfo[i] << "\n"; //and pushes them to the file 
            }
            store << "E\n"; //marks end of layer information
            for(int i = 0; i < layers.size(); i++){//for each layer
                for(int j = 0; j < layers[i].matrix.size(); j++){ //for each row in that matrix
                    for(int k = 0; k < layers[i].matrix[j].size(); k++){ //for each entire in that row
                        store << layers[i].matrix[j][k] << '\n';//push that entire into the file
                    }
                }
            }
            store.close(); //close 
        }
        //note this doesnt store the changes for momentum based gradient decent 
        //------------Load Model------------
        //pulls all the information of the model from the file given
        void loadModel(string path){
            ifstream file; //opens file
            file.open(path);
            string store;
            vector<int> matInfo; //vector for matrix struture info
            while(true){ //gets 
                getline(file,store,'\n'); //gets lines until its sees a 'E' which marks the end of the matrix structure info
                if(store == "E"){
                    break;
                }
                matInfo.push_back(stoi(store)); //pushs info to the vector
            }
            for(int i = 0; i < matInfo.size(); i++){ //then for each layer (which is the same as each entire in the vector of matrix info)
                vector<vector<float> > newMat; //makes a new matrix
                for(int j = 0; j < matInfo[i]; j++){ //then for the size of the a particalur layer, (this determines how many rows)
                    vector<float> newRow; //makes a new row
                    if(i == 0){ //if its the first layer
                        for(int k = 0; k < matInfo[i]; k++){ //the matrix will be square, so number of columns is the number of rows in this matirx
                            getline(file,store,'\n');
                            newRow.push_back(stof(store)); //pushs the weight value from the file 
                        }
                    } else{ //if its not, then 
                        for(int k = 0; k < matInfo[i-1]; k++){ //the matrix will be maybe not be square, so number of columns is the number of rows in this matirx before it
                            getline(file,store,'\n'); //gets weight from file
                            newRow.push_back(stof(store)); 
                        }
                    }
                    newMat.push_back(newRow); //pushs the row
                }                 
                Matrix newM(newMat); //makes the matrix a matrix object and then pushs it
                this->addLayer(newM); //adds it to the layers

            }
            for(int i = 0; i < matInfo.size(); i++){ //then it adds the matrix struture to the model object itself to used later
                _layerInfo.push_back(matInfo[i]);
            }
            file.close();
        }

        //------------Training the Model function------------
        //Training function that takes in a feature vector and the label for that example
        //and trains the models weights based off this example
        void predictWithtraining(vector<float> featureVector, vector<float> label){
            vector<vector<float> > activations; //matrix of activations that are recroded as predictions are made 
            vector<vector<float> > deltas; //matrix of deltas to be recorded 
            activations.push_back(featureVector); //pushes the feature vector to the list of activations as it is the first one 
            //------------Calculate prediction----------
            for(int i = 0; i < layers.size(); i ++){  //feature vector is matrix multipled by the matirx of weights for that layer
                featureVector = layers[i] * featureVector;
                featureVector = sigmoidVectorversion(featureVector); //then passes it through the sigmod function to smush it
                //? featureVector = reluvector(featureVector);//-------RELU-------
                activations.push_back(featureVector); //adds the new feature vector, to the activations function
            }
            //------------Calculate deltas for layer output---------- 
            vector <float> deltaOut; //finds desired changes, ie deltas, to the ouput nodes (these will be used later)
            for(int i = 0; i < layers[(layers.size()-1)].matrix.size(); i++){ //cycles through all the nodes in the ouput layer
                float in = (activations[activations.size()-2]) * (layers[layers.size()-1].matrix[i]); //finds activaitons of the layer before it
                float error = findLoss(i,label,featureVector);  //finds error
                float del = error * sigmoidDer(in);  //calcuates the desired change
                //? float del = error * reluD(in);//-------RELU-------
                if(isnan(del)){ //checks if it is NAN 
                    del = 0; //if so, makes it zero
                }
                deltaOut.push_back(del);
            }
            deltas.push_back(deltaOut); //pushs to overal delta list 
            int iterator = 3;
            int iterator2 = 0;
            
            //------------Calculate deltas for other layers----------
            for(int i = (layers.size()-2); i >= 0; i--){ //for all other layers other then the last ouput layer
                vector <float> deltasForl;
                for(int j = 0; j < layers[i].matrix.size(); j++){ //for each node in that layer starting at the end  
                    float in = activations[activations.size()-iterator] * layers[i].matrix[j];  //calculates the acitvations from the layer before it 
                    float sigDer = sigmoidDer(in); //
                    //?float sigDer = reluD(in); //-------RELU-------
                    float weightAnddeltaSum = (deltas[iterator2] * (layers[i+1].getColumnvec(j))); 
                    deltasForl.push_back(sigDer * weightAnddeltaSum); //adds delta to list 
                }
                deltas.push_back(deltasForl); //adds delta vector to matrix
                iterator++;
                iterator2++;
            }
            
            vector<Matrix> newLayers;
            vector<Matrix> newBigchange;
            iterator = 1;
            //------------Change weights for other stuff----------
            for(int i = 0; i < layers.size(); i++){ //what layer
                vector<vector<float> > newMod; //new list of weigths 
                vector<vector<float> > newChange; //new list of changes
                for(int j = 0; j < layers[i].matrix.size(); j++){ //what node
                    vector<float> newrow; //new row for model
                    vector<float> newCrow;//new row change list
                    for(int k = 0; k < layers[i].matrix[j].size(); k++){ //what weight
                        float change = activations[i][k] * deltas[deltas.size()-iterator][j]; //calcuates change 
                        //momentum bassed 
                        //change = beta1 * previousChanges[i].matrix[j][k] + (1-beta1) * change; //^REMOVE IN CASE OF EMERGENCY
                        if(isnan(change)){ //if the chaneg is NAN, sets it to zero
                            change = 0;
                        }
                        newCrow.push_back(change); //adds change to thes change lsit
                        float alphaAanddelta = learningRate * change; //times by learning rate and the this vlaue is
                        newrow.push_back(layers[i].matrix[j][k] + alphaAanddelta); //added to the old weight and pushed to new row for the weights
                    }   
                    newMod.push_back(newrow); //pushs new row to the matirx
                    newChange.push_back(newCrow); //same for chanegs 
                } 
                iterator++;
                newLayers.push_back(newMod); //push the new matirx to the list of new layers 
                newBigchange.push_back(newChange); //same for changes 
            } 
            resetLayers(newLayers); //replaces the old layers with the new updated layers
            resetChanges(newBigchange);//replaces the old changes with the new updated changes 
        }
 
};

#endif