#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
    Vector v1, v2;
    cout << "Nhap vector v1!\n";
    cin >> v1;
    cout << "Nhap vector v2!\n";
    cin >> v2;

    cout << "\nv1 = " << v1;
    cout << "\nv2 = " << v2;

    cout << "\n\nDo dai cua v1: " << v1.tinhDoDai();
    cout << "\nDo dai cua v2: " << v2.tinhDoDai();

    if (v1.getN() != v2.getN())
    {
        cout << "\nHai vector khong cung chieu, khong the thuc hien phep toan!\n";
        return 0;
    }
    cout << "\n\nv1 + v2 = " << v1 + v2;
    cout << "\nv1 - v2 = " << v1 - v2;
    cout << "\nNhap he so k: ";
    double k;
    cin >> k;
    cout << "\nv1 * k = " << v1 * k;
    cout << "\nv1 . v2 = " << v1 * v2;
    cout << '\n';

    return 0;
}