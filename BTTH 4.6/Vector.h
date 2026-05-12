#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector
{
private:
    int n;
    double *a;

public:
    Vector();
    Vector(int n);
    Vector(const Vector &v);
    ~Vector();

    friend istream &operator>>(istream &is, Vector &v);
    friend ostream &operator<<(ostream &os, Vector v);

    double tinhDoDai();
    Vector operator+(Vector &v);
    Vector operator-(Vector &v);
    Vector operator*(double k);
    double operator*(Vector &v);
    Vector &operator=(const Vector &v);
    int getN();
};

#endif