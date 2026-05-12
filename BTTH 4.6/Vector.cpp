#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include "Vector.h"

using namespace std;

// Hàm kiểm tra và xác nhận nhập từ người dùng có hợp lệ hay không
double kiemTraNhap(const string &error)
{
    double val;
    while (1)
    {
        cout << error;  // Hiển thị thông báo nhập
        if (cin >> val) // Kiểm tra có thành công hay không
        {
            if (cin.peek() == '\n') // Kiểm tra có ký tự hưa sau không
                break;              // Nếu đúng, thoát vòng lặp
        }
        else // Nếu nhập sai
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa nhập dư thừa
        }
    }
    return val; // Trả về giá trị hợp lệ
}

// Constructor mặc định - tạo vector rỗng
Vector::Vector()
{
    this->n = 0;       // Số chiều = 0
    this->a = nullptr; // Chưa cấp phát tọa độ
}

// Constructor - tạo vector với số chiều n
Vector::Vector(int n)
{
    this->n = n;             // Gán số chiều
    this->a = new double[n]; // Cấp phát bộ nhớ cho các tọa độ
}

// Destructor - giải phóng bộ nhớ cấp phát
Vector::~Vector()
{
    if (a != nullptr) // Kiểm tra có cấp phát không
    {
        delete[] a;  // Giải phóng mảng tọa độ
        a = nullptr; // Đặt về null để tránh con trỏ đảo
    }
}

// Copy constructor - sao chép sâu (deep copy)
Vector::Vector(const Vector &v)
{
    this->n = v.n;              // Sao chép số chiều
    this->a = new double[n];    // Cấp phát bộ nhớ mới
    for (int i = 0; i < n; i++) // Sao chép từng tọa độ
        this->a[i] = v.a[i];
}

// Toán tử gán - cấp phát giá trị từ vector khác (deep copy)
Vector &Vector::operator=(const Vector &v)
{
    if (this == &v) // Nếu gán cho chính nó, bỏ qua
        return *this;

    if (a != nullptr) // Giải phóng bộ nhớ cũ nếu có
        delete[] a;

    this->n = v.n;              // Sao chép số chiều
    this->a = new double[n];    // Cấp phát bộ nhớ mới
    for (int i = 0; i < n; i++) // Sao chép từng tọa độ
        this->a[i] = v.a[i];

    return *this; // Trả về tham chiếu đến object hiện tại
}

// Toán tử nhập - đọc vector từ bàn phím
istream &operator>>(istream &is, Vector &v)
{
    // Nhập và xác nhận số chiều hợp lệ
    while (1)
    {
        v.n = kiemTraNhap("Nhap so chieu: ");
        if (v.n >= 1) // Kiểm tra số chiều >= 1
            break;
        else
            cout << "So chieu toi thieu la 1. Vui long nhap lai!\n";
    }

    v.a = new double[v.n]; // Cấp phát bộ nhớ
    cout << "Nhap toa do cua vector!\n";
    for (int i = 0; i < v.n; i++) // Nhập từng tọa độ
    {
        string s = "Nhap toa do " + to_string(i + 1) + ": ";
        v.a[i] = kiemTraNhap(s);
    }

    return is; // Trả về input stream
}

// Toán tử xuất - in vector
ostream &operator<<(ostream &os, Vector v)
{
    os << "("; // In dấu mở ngoặc
    for (int i = 0; i < v.n; i++)
    {
        if (i > 0) // Thêm dấu phẩy nếu không phải phần tử đầu
            os << ", ";
        os << v.a[i]; // In tọa độ
    }
    os << ")"; // In dấu đóng ngoặc

    return os; // Trả về output stream
}

// Tính độ dài (chuẩn Euclidean) của vector
double Vector::tinhDoDai()
{
    double len = 0;             // Tổng các bình phương
    for (int i = 0; i < n; i++) // Tính tổng bình phương các tọa độ
        len += pow(a[i], 2);
    return sqrt(len); // Trả về căn bậc 2
}

// Toán tử cộng - tổng hai vector
Vector Vector::operator+(Vector &v)
{
    Vector res;                     // Tạo vector kết quả
    res.n = n;                      // Gán số chiều
    res.a = new double[res.n];      // Cấp phát bộ nhớ
    for (int i = 0; i < res.n; i++) // Cộng từng tọa độ tương ứng
        res.a[i] = a[i] + v.a[i];

    return res; // Trả về vector tổng
}

// Toán tử trừ - hiệu hai vector
Vector Vector::operator-(Vector &v)
{
    Vector res;                     // Tạo vector kết quả
    res.n = n;                      // Gán số chiều
    res.a = new double[res.n];      // Cấp phát bộ nhớ
    for (int i = 0; i < res.n; i++) // Trừ từng tọa độ tương ứng
        res.a[i] = a[i] - v.a[i];

    return res; // Trả về vector hiệu
}

// Toán tử nhân - nhân vector với số thực
Vector Vector::operator*(double k)
{
    Vector res;                     // Tạo vector kết quả
    res.n = n;                      // Gán số chiều
    res.a = new double[res.n];      // Cấp phát bộ nhớ
    for (int i = 0; i < res.n; i++) // Nhân từng tọa độ với hệ số k
        res.a[i] = a[i] * k;

    return res; // Trả về vector nhân
}

// Toán tử nhân - tích vô hướng của hai vector
double Vector::operator*(Vector &v)
{
    double sum = 0;             // Tích vô hướng
    for (int i = 0; i < n; i++) // Tính tích vô hướng
        sum += a[i] * v.a[i];

    return sum; // Trả về giá trị tích vô hướng
}

int Vector::getN()
{
    return n; // Trả về số chiều của vector
}