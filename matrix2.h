#ifndef MATRIX_H
#define MATRIX_H

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

class Matrix2
{
private:
    string _determinant;
    string _dimRow;
    string _dimCol;
    string _dimNul;
    int _rows;
    int _cols;
    vector<vector<float> > _matrix;

public:
    Matrix2();
    Matrix2(int rows, int cols);
    Matrix2(string instr);
    Matrix2(Matrix2 &copyMatrix);
    Matrix2 operator*(Matrix2 &matrix); // creates an entirely new matrix since multiplication can change the size
    Matrix2 operator%(Matrix2 &matrix); // factorization algorithm
    const int returnRow();
    const int returnCol();
    void setDim(int rows, int cols);
    void operator+=(Matrix2 &matrix);
    Matrix2 operator-(Matrix2 &matrix);
    void operator*=(float scal);
    void display();
    void fperror();
    void write(int row, int col, float entry);
    void augment(int cols);
    float retrieve(int row, int col);
    void pivot(Matrix2 &matrix, int targetCol, int startRow);
    bool resize(Matrix2 &matrix); // resizing function for empty matrices
};

#endif

//SOLI
//DEO
//GLORIA