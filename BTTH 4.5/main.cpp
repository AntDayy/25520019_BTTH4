#include <iostream>
#include "DaThuc.h"

using namespace std;

int main()
{
    DaThuc a, b;
    cout << "Nhap da thuc A!\n";
    cin >> a;
    cout << "Nhap da thuc B!\n";
    cin >> b;

    double x;
    cout << "\nNhap gia tri cua x: ";
    cin >> x;
    cout << "Gia tri cua da thuc A: " << a.tinhGiaTri(x) << endl;
    cout << "Gia tri cua da thuc B: " << b.tinhGiaTri(x) << endl;

    cout << "\nA + B = " << a + b << endl;
    cout << "A - B = " << a - b << endl;
    cout << "A * B = " << a * b << endl;

    return 0;
}