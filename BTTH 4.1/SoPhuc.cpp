#include <iostream>
#include "SoPhuc.h"
#include <limits>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Hàm hỗ trợ: Kiểm tra và ép buộc người dùng nhập đúng định dạng số
// Nhận vào một chuỗi thông báo lỗi (error) để in ra khi cần
float kiemTraNhap(const string &error)
{
    float value;
    // Vòng lặp vô hạn, chỉ thoát ra (break) khi người dùng nhập đúng
    while (1)
    {
        cout << error;
        // Kiểm tra xem việc trích xuất dữ liệu từ cin vào biến value có thành công hay không
        if (cin >> value)
        {
            // Kiểm tra ký tự tiếp theo trong bộ đệm. Nếu là '\n' (Enter) thì dữ liệu hợp lệ
            if (cin.peek() == '\n')
                break;
            else
                cout << "Vui long nhap lai!\n"; // Trường hợp nhập số kèm theo chữ (VD: 12abc)
        }
        else
        {
            // Nếu cin >> value thất bại (nhập toàn chữ)
            cout << "Vui long chi nhap so nguyen!\n";
            cin.clear();                                         // Xóa cờ lỗi của luồng cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ toàn bộ dữ liệu rác còn kẹt trong bộ đệm
        }
    }
    return value;
}

// Constructor mặc định: Khởi tạo số phức có giá trị 0 + 0i
SoPhuc::SoPhuc()
{
    this->Thuc = 0;
    this->Ao = 0;
}

// Constructor có tham số: Khởi tạo số phức với giá trị thực và ảo được truyền vào
SoPhuc::SoPhuc(float thuc, float ao)
{
    this->Thuc = thuc;
    this->Ao = ao;
}

// Destructor: Hàm hủy (hiện tại không cấp phát động nên để trống)
SoPhuc::~SoPhuc() {};

// Toán tử nhập (>>): Cho phép nhập đối tượng SoPhuc trực tiếp từ cin
istream &operator>>(istream &is, SoPhuc &sp)
{
    // Gọi hàm kiemTraNhap để đảm bảo dữ liệu nhập vào không bị lỗi
    sp.Thuc = kiemTraNhap("Nhap phan thuc: ");
    sp.Ao = kiemTraNhap("Nhap phan ao: ");
    return is;
}

// Toán tử xuất (<<): Trình bày số phức ra màn hình với định dạng tối ưu nhất
ostream &operator<<(ostream &os, const SoPhuc &sp)
{
    // Trường hợp số phức là 0 (phần thực = 0, phần ảo = 0)
    if (sp.Thuc == 0 && sp.Ao == 0)
    {
        os << 0;
        return os;
    }

    // Nếu phần thực khác 0, in phần thực ra trước
    if (sp.Thuc != 0)
    {
        os << sp.Thuc;
    }

    // Nếu phần ảo khác 0, tiến hành định dạng dấu + hoặc -
    if (sp.Ao != 0)
    {
        if (sp.Thuc != 0) // Đã có phần thực phía trước
        {
            if (sp.Ao > 0)
                os << " + " << sp.Ao << "i";
            else
                os << " - " << -sp.Ao << "i"; // Dùng -sp.Ao để không bị in ra 2 dấu trừ liền nhau
        }
        else // Khuyết phần thực (chỉ có phần ảo)
        {
            os << sp.Ao << "i";
        }
    }

    return os;
}

// Toán tử cộng (+): Trả về một đối tượng SoPhuc mới là tổng của 2 số phức
SoPhuc SoPhuc::operator+(const SoPhuc &sp)
{
    return SoPhuc(Thuc + sp.Thuc, Ao + sp.Ao);
}

// Toán tử trừ (-): Trả về một đối tượng SoPhuc mới là hiệu của 2 số phức
SoPhuc SoPhuc::operator-(const SoPhuc &sp)
{
    return SoPhuc(Thuc - sp.Thuc, Ao - sp.Ao);
}

// Toán tử nhân (*): Trả về một đối tượng SoPhuc mới là tích của 2 số phức theo công thức nhân
SoPhuc SoPhuc::operator*(const SoPhuc &sp)
{
    return SoPhuc(Thuc * sp.Thuc - Ao * sp.Ao, Thuc * sp.Ao + Ao * sp.Thuc);
}

// Toán tử chia (/): Trả về một đối tượng SoPhuc mới là thương của 2 số phức
SoPhuc SoPhuc::operator/(const SoPhuc &sp)
{
    SoPhuc res;
    // Tính mẫu số (a^2 + b^2 của số phức bị chia)
    float mau = sp.Thuc * sp.Thuc + sp.Ao * sp.Ao;

    // Kiểm tra lỗi chia cho 0
    if (mau == 0.0f)
    {
        throw std::invalid_argument("Loi: Khong the chia cho so phuc 0!");
    }

    // Tính phần thực và phần ảo cho số phức kết quả
    res.Thuc = (Thuc * sp.Thuc + Ao * sp.Ao) / mau;
    res.Ao = (-(Thuc * sp.Ao) + Ao * sp.Thuc) / mau;

    return res;
}

// Toán tử bằng (==): Kiểm tra 2 số phức có hoàn toàn giống nhau không
bool SoPhuc::operator==(const SoPhuc &sp)
{
    return (Thuc == sp.Thuc && Ao == sp.Ao);
}

// Toán tử khác (!=): Kiểm tra 2 số phức có khác biệt nhau hay không
bool SoPhuc::operator!=(const SoPhuc &sp)
{
    return (Thuc != sp.Thuc && Ao != sp.Ao);
}