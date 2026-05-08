#ifndef DATE_H
#define DATE_H
#include <iostream>

using namespace std;

class Date
{
private:
    int ngay;
    int thang;
    int nam;

public:
    Date();
    Date(int ngay, int thang, int nam);
    ~Date();

    friend istream &operator>>(istream &is, Date &d);
    friend ostream &operator<<(ostream &os, Date d);

    Date operator+(int n);
    Date operator-(int n);
    Date operator++();
    Date operator++(int);
    Date operator--();
    Date operator--(int);
    int operator-(Date &d);
    long long tinhNgay(Date &d);
};

#endif