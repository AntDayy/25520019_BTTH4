#include <iostream>
#include "SoPhuc.h"

using namespace std;

int main()
{
    SoPhuc a, b;
    cout << "Nhap so phuc A!\n";
    cin >> a;
    cout << "Nhap so phuc B!\n";
    cin >> b;

    cout << "\nSo phuc A: ";
    cout << a;
    cout << "\nSo phuc B: ";
    cout << b;

    cout << "\n\nA + B: " << a + b;
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
        cout << "\nSo phuc A bang so phuc B!\n";
    else if (a != b)
        cout << "\nSo phuc A khong bang so phuc B!\n";

    return 0;
}