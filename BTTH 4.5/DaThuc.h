#ifndef DATHUC_H
#define DATHUC_H
#include <iostream>

using namespace std;

class DaThuc
{
private:
    int n;
    double *a;

public:
    DaThuc();
    DaThuc(int n);
    DaThuc(const DaThuc &dt);
    ~DaThuc();

    friend istream &operator>>(istream &is, DaThuc &dt);
    friend ostream &operator<<(ostream &os, DaThuc dt);

    double tinhGiaTri(double x);
    DaThuc operator+(DaThuc &dt);
    DaThuc operator-(DaThuc &dt);
    DaThuc operator*(DaThuc &dt);
};

#endif