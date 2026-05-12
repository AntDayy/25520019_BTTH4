#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
    Date a, b;
    cout << "Nhap ngay thang nam!\n";
    cin >> a;
    cout << "Ngay thang nam ban vua nhap: " << a << endl;

    int n;
    cout << "Nhap so ngay ban muon cong: ";
    cin >> n;
    cout << "Ngay thang nam sau khi cong: " << a + n << endl;
    cout << "Nhap so ngay ban muon tru: ";
    cin >> n;
    cout << "Ngay thang nam sau khi tru: " << a - n << endl;

    cout << "Ngay thang nam sau khi tang 1 ngay: " << ++a;
    cout << "Ngay thang nam sau khi giam 1 ngay: " << --a << endl;

    cout << "Nhap ngay thang nam!\n";
    cin >> b;
    cout << "Khoang cach giua 2 moc thoi gian : " << a - b << " ngay" << endl;

    return 0;
}