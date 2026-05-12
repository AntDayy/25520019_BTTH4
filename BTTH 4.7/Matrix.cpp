#include <iostream>
#include <limits>
#include <iomanip>
#include "Matrix.h"

using namespace std;

// Hàm hỗ trợ kiểm tra nhập liệu, đảm bảo người dùng nhập đúng số thực
double kiemTraNhap(const string &error)
{
    double val;
    while (1)
    {
        cout << error;
        if (cin >> val) // Nhập thành công số thực
        {
            if (cin.peek() == '\n')
                break; // Không có ký tự rác đi kèm
        }
        else // Nhập sai (ký tự, chữ cái...)
        {
            cout << "[!] Lỗi. Vui lòng nhập lại!\n";
            cin.clear();                                         // Xóa cờ lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
        }
    }
    return val;
}

// Constructor mặc định: khởi tạo ma trận rỗng
Matrix::Matrix()
{
    this->m = 0;
    this->n = 0;
    this->a = nullptr;
}

// Constructor có tham số: cấp phát bộ nhớ cho ma trận m hàng n cột
Matrix::Matrix(int m, int n)
{
    this->m = m;
    this->n = n;
    this->a = new double *[m];
    for (int i = 0; i < m; i++)
        this->a[i] = new double[n];
}

// Copy constructor
Matrix::Matrix(const Matrix &mat)
{
    this->m = mat.m;
    this->n = mat.n;
    this->a = new double *[m];
    for (int i = 0; i < m; i++)
    {
        this->a[i] = new double[n];
        for (int j = 0; j < n; j++)
            this->a[i][j] = mat.a[i][j];
    }
}

// Destructor: giải phóng bộ nhớ động khi đối tượng bị hủy
Matrix::~Matrix()
{
    if (a != nullptr)
    {
        for (int i = 0; i < m; i++)
            delete[] a[i]; // Giải phóng từng hàng
        delete[] a;        // Giải phóng mảng con trỏ hàng
        a = nullptr;
    }
}

// Nạp chồng toán tử nhập >>: nhập kích thước và từng phần tử ma trận
istream &operator>>(istream &is, Matrix &mat)
{
    // Nhập và kiểm tra số dòng hợp lệ
    while (1)
    {
        mat.m = kiemTraNhap("Nhap so dong: ");
        if (mat.m >= 1)
            break;
        else
            cout << "[!] Loi. Vui long nhap so dong lon hon 0!\n";
    }

    // Nhập và kiểm tra số cột hợp lệ
    while (1)
    {
        mat.n = kiemTraNhap("Nhap so cot: ");
        if (mat.n >= 1)
            break;
        else
            cout << "[!] Loi. Vui long nhap so cot lon hon 0!\n";
    }

    // Cấp phát bộ nhớ dựa trên kích thước vừa nhập
    mat.a = new double *[mat.m];
    for (int i = 0; i < mat.m; i++)
        mat.a[i] = new double[mat.n];

    // Nhập giá trị cho từng ô trong ma trận
    cout << "Nhap gia tri cua tung phan tu!\n";
    for (int i = 0; i < mat.m; i++)
    {
        for (int j = 0; j < mat.n; j++)
            is >> mat.a[i][j];
    }

    return is;
}

// Nạp chồng toán tử xuất <<: hiển thị ma trận với định dạng ngoặc vuông
ostream &operator<<(ostream &os, Matrix mat)
{
    for (int i = 0; i < mat.m; i++)
    {
        os << "[ "; // Bắt đầu hàng
        for (int j = 0; j < mat.n; j++)
            os << setw(8) << mat.a[i][j] << " "; // Căn lề 8 khoảng trắng
        os << "]" << endl;                       // Kết thúc hàng
    }
    return os;
}

// Lấy số cột của ma trận
int Matrix::getCol()
{
    return n;
}

// Lấy số dòng của ma trận
int Matrix::getRow()
{
    return m;
}

// Nạp chồng toán tử +: cộng hai ma trận cùng kích thước
Matrix Matrix::operator+(Matrix &mat)
{
    Matrix res(m, n); // Ma trận tạm chứa kết quả
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            res.a[i][j] = a[i][j] + mat.a[i][j]; // Cộng từng vị trí tương ứng
    }
    return res;
}

// Nạp chồng toán tử -: trừ hai ma trận cùng kích thước
Matrix Matrix::operator-(Matrix &mat)
{
    Matrix res(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            res.a[i][j] = a[i][j] - mat.a[i][j]; // Trừ từng vị trí tương ứng
    }
    return res;
}

// Nạp chồng toán tử *: nhân hai ma trận (Hàng nhân Cột)
Matrix Matrix::operator*(Matrix &mat)
{
    Matrix res(m, mat.n); // Kết quả có số hàng của ma trận 1 và số cột của ma trận 2
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < mat.n; j++)
        {
            res.a[i][j] = 0; // Khởi tạo giá trị tích lũy
            for (int k = 0; k < n; k++)
                res.a[i][j] += a[i][k] * mat.a[k][j]; // Công thức nhân ma trận
        }
    }
    return res;
}

// Nạp chồng toán tử *: nhân ma trận với một vector
Matrix Matrix::operator*(vector<double> &v)
{
    Matrix res(m, 1); // Kết quả là một ma trận cột (m hàng, 1 cột)
    for (int i = 0; i < m; i++)
    {
        res.a[i][0] = 0; // Luôn thao tác trên cột duy nhất (chỉ số 0)
        for (int j = 0; j < n; j++)
            res.a[i][0] += a[i][j] * v[j]; // Tổng tích hàng ma trận với phần tử vector
    }
    return res;
}