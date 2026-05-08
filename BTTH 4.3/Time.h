#ifndef TIME_H
#define TIME_H
#include <iostream>

using namespace std;

class Time
{
private:
    int gio;
    int phut;
    int giay;

public:
    Time();
    Time(int gio, int phut, int giay);
    ~Time();

    friend istream &operator>>(istream &is, Time &t);
    friend ostream &operator<<(ostream &os, Time t);

    Time operator+(int n);
    Time operator-(int n);
    Time operator++();
    Time operator++(int);
    Time operator--();
    Time operator--(int);
};

#endif