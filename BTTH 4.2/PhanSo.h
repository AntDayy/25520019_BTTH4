#ifndef PHANSO_H
#define PHANSO_H
#include <iostream>

using namespace std;

class PhanSo
{
private:
    int tu;
    int mau;

public:
    PhanSo();
    PhanSo(int tu, int mau = 1);
    ~PhanSo();

    friend istream &operator>>(istream &is, PhanSo &ps);
    friend ostream &operator<<(ostream &os, const PhanSo &ps);

    PhanSo operator+(const PhanSo &ps);
    PhanSo operator-(const PhanSo &ps);
    PhanSo operator*(const PhanSo &ps);
    PhanSo operator/(const PhanSo &ps);
    bool operator==(const PhanSo &ps);
    bool operator>(const PhanSo &ps);
    bool operator<(const PhanSo &ps);
};

#endif