#include <iostream>
#include <limits>
#include <cmath>
#include "Date.h"

using namespace std;

int kiemTraNhap(const string &error)
{
    int value;

    while (1)
    {
        cout << error;
        if (cin >> value)
        {
            if (cin.peek() == '\n')
                break;
            else
                cout << "Vui long nhap lai! \n";
        }
        else
        {
            cout << "Vui long chi nhap so nguyen! \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return value;
}

bool kiemTraNamNhuan(int nam)
{
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

int traVeSoNgay(int thang, int nam)
{
    switch (thang)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return (kiemTraNamNhuan(nam) ? 29 : 28);
    default:
        return 0;
    }
}

bool kiemTraHopLe(int ngay, int thang, int nam)
{
    if (nam <= 0 || thang > 12 || thang < 1)
        return false;
    if (ngay > traVeSoNgay(thang, nam) || ngay < 1)
        return false;
    return true;
}

Date::Date()
{
    this->ngay = 1;
    this->thang = 1;
    this->nam = 1;
}

Date::Date(int ngay, int thang, int nam)
{
    this->ngay = ngay;
    this->thang = thang;
    this->nam = nam;
}

Date::~Date() {}

istream &operator>>(istream &is, Date &d)
{
    while (1)
    {
        d.ngay = kiemTraNhap("Nhap ngay: ");
        d.thang = kiemTraNhap("Nhap thang: ");
        d.nam = kiemTraNhap("Nhap nam: ");

        if (kiemTraHopLe(d.ngay, d.thang, d.nam))
            break;
        else
            cout << "Ngay thang nam khong hop le. Vui long nhap lai! \n";
    }
    return is;
}

ostream &operator<<(ostream &os, Date d)
{
    os << d.ngay << "/" << d.thang << "/" << d.nam << endl;
    return os;
}

Date Date::operator+(int n)
{
    Date d = *this;
    d.ngay += n;

    if (d.ngay > traVeSoNgay(d.thang, d.nam))
    {
        d.ngay = 1;
        d.nam += d.thang / 12;
        d.thang = (d.thang % 12) + 1;
    }

    return d;
}

Date Date::operator-(int n)
{
    Date d = *this;
    d.ngay -= n;

    if (d.ngay < 1)
    {
        d.thang--;
        if (d.thang < 1)
        {
            d.thang = 12;
            d.nam--;
        }
        d.ngay += traVeSoNgay(d.thang, d.nam);
    }

    return d;
}

Date Date::operator++()
{
    *this = (*this) + 1;
    return *this;
}

Date Date::operator++(int)
{
    Date d = *this;
    *this = (*this) + 1;
    return d;
}

Date Date::operator--()
{
    *this = (*this) - 1;
    return *this;
}

Date Date::operator--(int)
{
    Date d = *this;
    *this = (*this) - 1;
    return d;
}

long long Date::tinhNgay(Date &d)
{
    long long distance = d.ngay;
    for (int i = 1; i < d.nam; i++)
        distance += (kiemTraNamNhuan(i)) ? 366 : 365;

    for (int i = 1; i < d.thang; i++)
        distance += traVeSoNgay(i, d.nam);

    return distance;
}

int Date::operator-(Date &d)
{
    return abs(tinhNgay(*this) - tinhNgay(d));
}