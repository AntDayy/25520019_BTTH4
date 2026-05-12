#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
    int m, n;
    double **a;

public:
    Matrix();
    Matrix(int m, int n);
    Matrix(const Matrix &mat);
    ~Matrix();

    friend istream &operator>>(istream &is, Matrix &mat);
    friend ostream &operator<<(ostream &os, Matrix mat);

    int getCol();
    int getRow();
    Matrix operator+(Matrix &mat);
    Matrix operator-(Matrix &mat);
    Matrix operator*(Matrix &mat);
    Matrix operator*(vector<double> &v);
};

#endif