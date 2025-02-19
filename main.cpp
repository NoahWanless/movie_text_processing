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
#include "model.h"
#include "random_functions.h"
#include "file.h"
#include <random>
using namespace std;

//uses this website to concentrate two vectors together 
//https://stackoverflow.com/questions/201718/concatenating-two-stdvectors

 //This website was used to shuffle two vectors:
 //https://cplusplus.com/forum/beginner/234369/

 //and this website was used for the random device to get better random numbers:
 //https://cplusplus.com/reference/random/random_device/?kw=random_device

//this website was used for the random number generator in the shuffling of the vectors below
 //https://cplusplus.com/reference/random/mt19937/?kw=mt19937


/* NOTE ON MAIN FUNCTION:
it is set up at this time to lodel in a pre trained model, if you wish to switch it to train a new model the required actions will
be marked with comments

NOTE: to change how many examples it trains off of, go to the 'file.h' file down to the funcitons getNegTrainData and getPosTrainData
and follw the instructions there
*/
int main(){
    int modelInfo[5] = {323,200,150,50,2};
    Model m;
    //Model m(modelInfo,5); //!--TO TRAIN NEW MODEL----uncomment this, and comment out the line before it, 42
    map<string, int> maping = createMap(); //creates mapping 
    vector<Review> pos = getPosTrainData(maping); //gets all positive training data
    vector<Review> neg = getNegTrainData(maping);//gets all negative training data
    cout << "combing lists" << endl;
    pos.insert(pos.end(), neg.begin(), neg.end()); //combines the lists 
    random_device rd; //random device to shuffle lists
    mt19937 g(rd()); //
    cout << "shuffling lists" << endl;
    shuffle(pos.begin(),pos.end(),g);
    //NOTE 3.0 version is already trained 
    m.loadModel("version3.0.txt");//!--TO TRAIN NEW MODEL----comment this
    //!this will make it so it doesnt load a new model in



    //!--TO TRAIN NEW MODEL----comment this out until the next marker below
    vector<float> thingy2;
    int nuM;
    cout << "Enter between 1 and 10" << endl;
    cin >> nuM; 
    for(int j = 0; j < pos[nuM].getData().size(); j++){
        thingy2.push_back(float(pos[nuM].getData()[j]));
    }
    vector<float> ouput2 = m.predict(thingy2); //makes prediction
    cout << "Label: "; 
    if(pos[nuM].getType()){ //displays label for that example
        cout << "positive" << endl;
    } else{
        cout << "negative" << endl;
    }
    if(ouput2[0] > ouput2[1]){ //displays classification
        cout << "The model has classified the example as positive" << endl;
    } else{
        cout << "The model has classified the example as negative" << endl;
    }
    //!--TO TRAIN NEW MODEL----comment this out all this above up to the marker


    //!--TO TRAIN NEW MODEL----uncomment all bellow
    // for(int i = 0; i < pos.size(); i++){
    //     vector<float> label;
    //     if(pos[i].getType() == 0){
    //         label.push_back(0);
    //         label.push_back(1);
    //     } else{
    //         label.push_back(1);
    //         label.push_back(0);
    //     }
    //     vector<float> thingy2;
    //     for(int j = 0; j < pos[i].getData().size(); j++){
    //         thingy2.push_back(float(pos[i].getData()[j]));
    //     }
    //     m.predictWithtraining(thingy2,label);
    //     if(i % 100 == 0){
    //         cout << "Example " << i << " trained!"<< endl;
    //     }
    // }
    // cout << "Training Done!"<< endl;

    // m.storeModel("version4.0.txt"); //!--TO TRAIN NEW MODEL----and change the file name you want the model you train to go to
    // cout << "Done Storing!" << endl;
    

}