#include <iostream>
#include <limits>
#include "time.h"

using namespace std;

// Hàm hỗ trợ: Kiểm tra và ép kiểu người dùng nhập vào phải là số nguyên
int kiemTraNhap(const string &error)
{
    int val;
    while (1)
    {
        cout << error;
        // Kiểm tra xem đầu vào có phải là số không và không có ký tự lạ đi kèm
        if (cin >> val)
        {
            if (cin.peek() == '\n')
                break; // Nhập đúng số nguyên, thoát vòng lặp
        }
        else
        {
            cout << "[!] Loi. Vui long nhap lai!\n";
            cin.clear();                                         // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
        }
    }
    return val;
}

Time::Time()
{
    this->gio = 0;
    this->phut = 0;
    this->giay = 0;
}

// Constructor có tham số: Khởi tạo thời gian theo giá trị truyền vào
Time::Time(int gio, int phut, int giay)
{
    this->gio = gio;
    this->phut = phut;
    this->giay = giay;
}

Time::~Time() {}

// Hàm hỗ trợ: Kiểm tra xem bộ Giờ:Phút:Giây có nằm trong giới hạn thực tế không
bool kiemTraHopLe(int gio, int phut, int giay)
{
    if (gio < 0 || gio >= 24 || phut < 0 || phut >= 60 || giay < 0 || giay >= 60)
        return false;

    return true;
}

// Nạp chồng toán tử nhập (>>): Cho phép cin trực tiếp đối tượng Time
istream &operator>>(istream &is, Time &t)
{
    while (1)
    {
        t.gio = kiemTraNhap("Nhap gio: ");
        t.phut = kiemTraNhap("Nhap phut: ");
        t.giay = kiemTraNhap("Nhap giay: ");

        // Nếu hợp lệ thì mới chấp nhận, nếu không bắt nhập lại cả bộ
        if (kiemTraHopLe(t.gio, t.phut, t.giay))
            break;
        else
            cout << "[!] Gio phut giay ban nhap khong hop le!\n";
    }

    return is;
}

// Nạp chồng toán tử xuất (<<): Định dạng thời gian theo kiểu hh:mm:ss
ostream &operator<<(ostream &os, Time t)
{
    // Sử dụng toán tử điều kiện để thêm số 0 phía trước nếu giá trị < 10
    os << (t.gio < 10 ? "0" : "") << t.gio << ":"
       << (t.phut < 10 ? "0" : "") << t.phut << ":"
       << (t.giay < 10 ? "0" : "") << t.giay << endl;

    return os;
}

// Nạp chồng toán tử cộng (Time + int): Tăng thêm n giây, trả về đối tượng mới
Time Time::operator+(int n)
{
    Time res = *this; // Tạo bản sao để không làm thay đổi đối tượng gốc
    // Bước 1: Quy đổi toàn bộ ra đơn vị giây để dễ tính toán
    long long sum = (long long)res.gio * 3600 + res.phut * 60 + res.giay + n;

    // Bước 2: Sử dụng chia lấy dư 86400 để thời gian luôn xoay vòng trong 24h
    sum %= 86400;
    if (sum < 0)
        sum += 86400; // Xử lý trường hợp n âm khiến tổng giây bị âm

    // Bước 3: Tính toán ngược lại từ tổng giây ra Giờ, Phút, Giây
    res.gio = sum / 3600;
    res.phut = (sum % 3600) / 60;
    res.giay = sum % 60;

    return res;
}

// Nạp chồng toán tử trừ (Time - int): Tận dụng phép cộng với số đối
Time Time::operator-(int n)
{
    return (*this) + (-n);
}

// Nạp chồng toán tử tiền tố ++ (++Time): Tăng 1 giây và trả về chính nó
Time Time::operator++()
{
    *this = (*this) + 1; // Cập nhật trực tiếp giá trị của đối tượng hiện tại
    return *this;
}

// Nạp chồng toán tử tiền tố -- (--Time): Giảm 1 giây và trả về chính nó
Time Time::operator--()
{
    *this = (*this) + (-1);
    return *this;
}

// Nạp chồng toán tử hậu tố ++ (Time++): Tăng 1 giây nhưng trả về giá trị cũ
Time Time::operator++(int)
{
    Time t = *this; // Lưu lại giá trị cũ (chưa tăng)
    ++(*this);      // Thực hiện tăng giá trị đối tượng hiện tại
    return t;       // Trả về giá trị cũ đã lưu
}

// Nạp chồng toán tử hậu tố -- (Time--): Giảm 1 giây nhưng trả về giá trị cũ
Time Time::operator--(int)
{
    Time t = *this; // Lưu lại giá trị cũ
    --(*this);      // Thực hiện giảm giá trị
    return t;       // Trả về giá trị cũ
}