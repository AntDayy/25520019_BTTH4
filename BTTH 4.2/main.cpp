#include <iostream>
#include "PhanSo.h"

using namespace std;

int main()
{
    PhanSo a, b;
    cout << "Nhap phan so A!\n";
    cin >> a;
    cout << "Nhap phan so B!\n";
    cin >> b;

    cout << "Phan so A: " << a << endl;
    cout << "Phan so B: " << b << endl;

    cout << "\nA + B: " << a + b;
    cout << "\nA - B: " << a - b;
    cout << "\nA * B: " << a * b;
    try
    {
        a / b;
        cout << "\nA / B: " << a / b << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    if (a == b)
        cout << "\nPhan so A bang phan so B!\n";
    else if (a > b)
        cout << "\nPhan so A lon hon phan so B!\n";
    else if (a < b)
        cout << "\nPhan so A nho hon phan so B!\n";

    return 0;
}