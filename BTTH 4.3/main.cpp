#include <iostream>
#include "Time.h"

using namespace std;

int main()
{
    Time t;
    cout << "Nhap gio phut giay!\n";
    cin >> t;
    cout << "\nGio phut giay ban vua nhap: " << t << endl;

    int n;
    cout << "Nhap so nguyen giay ban muon cong: ";
    cin >> n;
    cout << "Gio phut giay sau khi cong: " << t + n << endl;
    cout << "Nhap so nguyen giay ban muon tru: ";
    cin >> n;
    cout << "Gio phut giay sau khi tru: " << t - n << endl;
    cout << "Gio phut giay sau khi tang them 1 giay: " << ++t;
    cout << "Gio phut giay sau khi tru di 1 giay: " << --t << endl;

    return 0;
}