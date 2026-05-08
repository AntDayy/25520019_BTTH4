#include <iostream>
#include <limits>
#include "DaThuc.h"

double kiemTraNhap(const string &error)
{
    double val;
    while (1) // Vòng lặp vô hạn cho đến khi nhập đúng
    {
        cout << error;
        if (cin >> val)
        {
            // Kiểm tra nếu ký tự tiếp theo là dấu Enter (xuống dòng) thì dữ liệu hợp lệ
            if (cin.peek() == '\n')
                break;
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa cờ lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ các ký tự bị kẹt trong bộ nhớ đệm
        }
    }
    return val;
}

DaThuc::DaThuc()
{
    this->n = 0;
    this->a = nullptr;
}

DaThuc::DaThuc(int n)
{
    this->n = n;
    this->a = new double[n + 1];
}

DaThuc::DaThuc(const DaThuc &dt)
{
    this->n = dt.n;
    if (dt.a != nullptr)
    {
        this->a = new double[this->n + 1];
        for (int i = 0; i <= this->n; i++)
        {
            this->a[i] = dt.a[i];
        }
    }
    else
    {
        this->a = nullptr;
    }
}

DaThuc::~DaThuc()
{
    if (a != nullptr)
    {
        delete[] a;
        a = nullptr;
    }
}

istream &operator>>(istream &is, DaThuc &dt)
{
    cout << "Nhap bac cua da thuc (n >= 0)!\n";
    while (1)
    {
        dt.n = kiemTraNhap("Nhap n: ");

        if (dt.n < 0)
            cout << "Vui long nhap n >= 0!\n";
        else
            break;
    }

    cout << "Da thuc ban nhap co dang: ";
    for (int i = 0; i <= dt.n; i++)
    {
        if (dt.n - i == 0)
        {
            cout << "a" << i + 1;
            continue;
        }
        cout << "a" << i + 1 << "x^" << dt.n - i;
        if (i < dt.n)
            cout << " + ";
    }
    cout << "\n";

    dt.a = new double[dt.n + 1];
    for (int i = 0; i <= dt.n; i++)
    {
        string cauNhac = "Nhap he so a" + to_string(i + 1) + ": ";
        dt.a[i] = kiemTraNhap(cauNhac);
    }

    return is;
}

ostream &operator<<(ostream &os, DaThuc dt)
{
    bool isAllZero = true;
    for (int i = 0; i <= dt.n; i++)
    {
        if (dt.a[i] == 0)
            continue;

        if (isAllZero == false)
        {
            if (dt.a[i] > 0)
                os << " + ";
            else
                os << " - ";
        }
        else
        {
            if (dt.a[i] < 0)
                os << "-";
        }

        isAllZero = false;
        double giatriTuyetDoi = abs(dt.a[i]);
        int bacThu_i = dt.n - i;

        if (giatriTuyetDoi != 1 || bacThu_i == 0)
            os << giatriTuyetDoi;

        if (bacThu_i > 0)
        {
            os << "x";
            if (bacThu_i > 1)
                os << "^" << bacThu_i;
        }
    }

    if (isAllZero == true)
        os << "0";

    return os;
}

double DaThuc::tinhGiaTri(double x)
{
    if (n < 0 || a == nullptr)
        return 0;

    double val = a[0];
    for (int i = 1; i <= n; i++)
        val = val * x + a[i];
    return val;
}

DaThuc DaThuc::operator+(DaThuc &dt)
{
    DaThuc res;
    // Bậc của đa thức kết quả tạm thời bằng bậc lớn nhất của 2 đa thức
    res.n = (this->n >= dt.n) ? this->n : dt.n;
    res.a = new double[res.n + 1];

    // Lặp ngược từ bậc thấp nhất lên bậc cao nhất để cộng các hệ số tương ứng
    for (int i = res.n; i >= 0; i--)
    {
        // Toán tử 3 ngôi: Đảm bảo nếu một đa thức bậc ngắn hơn thì hệ số bị thiếu coi như là 0
        double heSo1 = (this->n - i >= 0) ? this->a[this->n - i] : 0;
        double heSo2 = (dt.n - i >= 0) ? dt.a[dt.n - i] : 0;

        res.a[res.n - i] = heSo1 + heSo2;
    }

    // Chuẩn hóa đa thức: Xử lý trường hợp cộng làm triệt tiêu hệ số bậc cao nhất
    int soBacBiGiam = 0;
    while (soBacBiGiam < res.n && res.a[soBacBiGiam] == 0)
    {
        soBacBiGiam++; // Đếm số lượng bậc vô nghĩa bị gán bằng 0 ở đầu mảng
    }

    // Nếu bị giảm bậc, cấp phát mảng mới nhỏ hơn và chép dữ liệu có ý nghĩa sang
    if (soBacBiGiam > 0)
    {
        int bacMoi = res.n - soBacBiGiam;
        double *mangMoi = new double[bacMoi + 1];
        for (int i = 0; i <= bacMoi; i++)
        {
            mangMoi[i] = res.a[soBacBiGiam + i];
        }
        delete[] res.a;  // Giải phóng mảng tạm cũ
        res.a = mangMoi; // Trỏ sang mảng mới đã chuẩn hóa
        res.n = bacMoi;
    }

    return res;
}

DaThuc DaThuc::operator-(DaThuc &dt)
{
    DaThuc res;
    // Bậc của đa thức kết quả tạm thời bằng bậc lớn nhất của 2 đa thức
    res.n = (this->n >= dt.n) ? this->n : dt.n;
    res.a = new double[res.n + 1];

    // Lặp ngược từ bậc thấp nhất lên bậc cao nhất để trừ các hệ số tương ứng
    for (int i = res.n; i >= 0; i--)
    {
        double heSo1 = (this->n - i >= 0) ? this->a[this->n - i] : 0;
        double heSo2 = (dt.n - i >= 0) ? dt.a[dt.n - i] : 0;

        res.a[res.n - i] = heSo1 - heSo2;
    }

    // Chuẩn hóa đa thức: Rút gọn mảng tương tự như hàm Cộng
    int soBacBiGiam = 0;
    while (soBacBiGiam < res.n && res.a[soBacBiGiam] == 0)
    {
        soBacBiGiam++;
    }

    if (soBacBiGiam > 0)
    {
        int bacMoi = res.n - soBacBiGiam;
        double *mangMoi = new double[bacMoi + 1];
        for (int i = 0; i <= bacMoi; i++)
        {
            mangMoi[i] = res.a[soBacBiGiam + i];
        }
        delete[] res.a;
        res.a = mangMoi;
        res.n = bacMoi;
    }

    return res;
}

DaThuc DaThuc::operator*(DaThuc &dt)
{
    // Bậc của đa thức mới bằng tổng bậc của hai đa thức thành phần
    int bacMoi = this->n + dt.n;
    DaThuc res(bacMoi);

    // Khởi tạo tất cả hệ số của đa thức kết quả bằng 0
    for (int k = 0; k <= bacMoi; k++)
    {
        res.a[k] = 0;
    }

    // Thực hiện nhân từng hạng tử
    for (int i = 0; i <= this->n; i++)
    {
        for (int j = 0; j <= dt.n; j++)
        {
            // Hệ số bậc (i+j) bằng tổng các tích của hệ số bậc i và bậc j
            res.a[i + j] += this->a[i] * dt.a[j];
        }
    }

    return res;
}