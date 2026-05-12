#include <iostream>
#include <limits>
#include "PhanSo.h"
#include <cmath>

using namespace std;

int kiemTraNhap(const string &error)
{
    int val;
    while (1)
    {
        cout << error;
        if (cin >> val)
        {
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return val;
}

PhanSo::PhanSo()
{
    this->tu = 0;
    this->mau = 1;
}

PhanSo::PhanSo(int tu, int mau)
{
    this->tu = tu;
    this->mau = mau;
}

PhanSo::~PhanSo() {};

istream &operator>>(istream &is, PhanSo &ps)
{
    ps.tu = kiemTraNhap("Nhap tu so: ");
    while (1)
    {
        ps.mau = kiemTraNhap("Nhap mau so: ");
        if (ps.mau != 0)
            break;
        else
            cout << "[!] Loi. Mau khong duoc bang 0!\n";
    }
    return is;
}

int timUCLN(int a, int b)
{
    if (b == 0)
        return a;
    return timUCLN(b, a % b);
}

ostream &operator<<(ostream &os, const PhanSo &ps)
{
    int t = ps.tu;
    int m = ps.mau;

    int ucln = timUCLN(abs(t), abs(m));
    t /= ucln;
    m /= ucln;

    if (m < 0)
    {
        t = -t;
        m = -m;
    }

    if (m == 1)
        os << t;
    else
        os << t << "/" << m;

    return os;
}

PhanSo PhanSo::operator+(const PhanSo &ps)
{
    return PhanSo(tu * ps.mau + ps.tu * mau, mau * ps.mau);
}

PhanSo PhanSo::operator-(const PhanSo &ps)
{
    return PhanSo(tu * ps.mau - ps.tu * mau, mau * ps.mau);
}

PhanSo PhanSo::operator*(const PhanSo &ps)
{
    return PhanSo(tu * ps.tu, mau * ps.mau);
}

PhanSo PhanSo::operator/(const PhanSo &ps)
{
    if (mau * ps.tu == 0)
    {
        throw std::invalid_argument("\nLoi: Mau cua phep chia bang 0!");
    }
    return PhanSo(tu * ps.mau, mau * ps.tu);
}

bool PhanSo::operator==(const PhanSo &ps)
{
    return ((double)tu / mau == (double)ps.tu / ps.mau);
}

bool PhanSo::operator>(const PhanSo &ps)
{
    return ((double)tu / mau > (double)ps.tu / ps.mau);
}

bool PhanSo::operator<(const PhanSo &ps)
{
    return ((double)tu / mau < (double)ps.tu / ps.mau);
}