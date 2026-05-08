#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix a, b;
    cout << "Nhap ma tran A!\n";
    cin >> a;
    cout << "Nhap ma tran B!\n";
    cin >> b;

    cout << "Ma tran A\n";
    cout << a;
    cout << "Ma tran B\n";
    cout << b;

    if (a.getCol() != b.getCol() || a.getRow() != b.getRow())
        cout << "Khong the thuc hien phep cong tru \ndo hai ma tran khong co cung kich thuoc!\n";
    else
    {
        cout << "A + B =\n";
        cout << a + b;
        cout << "A - B =\n";
        cout << a - b;
    }
    if (a.getCol() != b.getRow())
        cout << "Khong the thuc hien phep nhan do \nso hang cua ma tran B khong bang so cot cua ma tran A!\n";
    else
    {
        cout << "A * B =\n";
        cout << a * b;
    }

    vector<double> v(a.getCol());
    cout << "Nhap toa do vector (" << a.getCol() << " phan tu): ";
    for (int i = 0; i < a.getCol(); i++)
        cin >> v[i];
    cout << "A * v =\n";
    Matrix res = a * v;
    cout << res;

    return 0;
}