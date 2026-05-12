#ifndef SOPHUC_H
#define SOPHUC_H
#include <iostream>

using namespace std;

class SoPhuc
{
private:
    float Thuc;
    float Ao;

public:
    SoPhuc();
    SoPhuc(float thuc, float ao);
    ~SoPhuc();

    friend istream &operator>>(istream &is, SoPhuc &sp);
    friend ostream &operator<<(ostream &os, const SoPhuc &sp);

    SoPhuc operator+(const SoPhuc &sp);
    SoPhuc operator-(const SoPhuc &sp);
    SoPhuc operator*(const SoPhuc &sp);
    SoPhuc operator/(const SoPhuc &sp);
    bool operator==(const SoPhuc &sp);
    bool operator!=(const SoPhuc &sp);
};

#endif