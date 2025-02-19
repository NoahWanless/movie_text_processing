#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>
#include <cstdint> 
#include <iomanip>
#include <cmath>
#include <vector>
#include <ctime>  
#include <cctype> 
#include <fstream>
using namespace std;


class Vec {
    private:
    int _norm;
    bool _isCol;
    vector<int>_vec;

    public:
    Vec();
    Vec(vector<float>vec);

    void operator*=(Vec &vec);
    void operator+=(Vec &vec);
    void operator-=(Vec &vec);
    void operator*=(float vec);
};

#endif