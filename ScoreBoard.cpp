#include "ScoreBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Hàm tạo tọa độ ngẫu nhiên cho thức ăn
void khoiTaoThucAn(int &thucAnX, int &thucAnY) {
    thucAnX = rand() % 40 + 5;
    thucAnY = rand() % 15 + 5;
}

// Hàm kiểm tra rắn ăn mồi, nếu ăn thì cộng điểm và tạo mồi mới
bool kiemTraAnMoi(int ranX, int ranY, int &thucAnX, int &thucAnY, int &diem) {
    if (ranX == thucAnX && ranY == thucAnY) {
        diem += 10; // Cộng 10 điểm
        khoiTaoThucAn(thucAnX, thucAnY); // Random cục mồi mới
        return true; // Trả về true báo hiệu đã ăn (để rắn dài ra)
    }
    return false; // Chưa ăn
}

// Hàm in điểm
void inDiem(int diem) {
    cout << "=== DIEM CUA BAN: " << diem << " ===" << endl;
}