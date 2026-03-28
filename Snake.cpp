#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

void gotoxy(int column, int line);

#ifndef _WIN32
int kbhit(void);
int getch(void);
#endif

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

struct Point{
    int x, y;
};

class CONRAN{
public:
    Point A[100];
    int DoDai;

    CONRAN(){
        DoDai = 3;
        A[0] = {10, 10};
        A[1] = {11, 10};
        A[2] = {12, 10};
    }

    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    void DiChuyen(int Huong){
        for (int i = DoDai - 1; i > 0; i--){
            A[i] = A[i - 1];
        }

        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;
    }
};

void gotoxy(int column, int line){
#ifdef _WIN32
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", line, column);
#endif
}

int main(){
    CONRAN r;
    int Huong = 0;
    char t;
    //khai bao va chay ham tao thuc an
    int thucAnX, thucAnY;
    int diem = 0;

    srand(time (0));
    khoiTaoThucAn(thucAnX,thucAnY);

    while (true){

        if (kbhit()){
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1; // đổi lại s cho chuẩn WASD
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        r.DiChuyen(Huong);

        // kiểm tra ăn mồi
        if (kiemTraAnMoi(r.A[0].x, r.A[0].y, thucAnX, thucAnY, diem)){
            r.DoDai++;
        }

        // vẽ mồi
        gotoxy(thucAnX, thucAnY);
        cout << "*";

        // vẽ rắn
        r.Ve();

        // in điểm
        gotoxy(0, 0);
        cout << "Diem: " << diem;


#ifdef _WIN32
        Sleep(300);
#else
        usleep(300000);
#endif
    }

    return 0;
}

#ifndef _WIN32

int kbhit(void){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void){
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif