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

// Ẩn con trỏ
#ifdef _WIN32
void AnConTro(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}
#else
void AnConTro(){
    printf("\033[?25l");
}
#endif

void gotoxy(int column, int line);

#ifndef _WIN32
int kbhit(void);
int getch(void);
#endif

// ================== THỨC ĂN ==================
void khoiTaoThucAn(int &thucAnX, int &thucAnY) {
    thucAnX = rand() % 40 + 5;
    thucAnY = rand() % 15 + 5;
}

bool kiemTraAnMoi(int ranX, int ranY, int &thucAnX, int &thucAnY, int &diem) {
    if (ranX == thucAnX && ranY == thucAnY) {
        diem += 10;
        khoiTaoThucAn(thucAnX, thucAnY);
        return true;
    }
    return false;
}

// ================== KHUNG ==================
void VeKhung(){
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 40; j++) {
            if(i == 0 && j == 0) cout << "o";
            else if(i == 0 && j == 39) cout << "o";
            else if(i == 19 && j == 0) cout << "o";
            else if(i == 19 && j == 39) cout << "o";
            else if(i == 0 || i == 19) cout << "-";
            else if(j == 0 || j == 39) cout << "|";
            else cout << " ";
        }
        cout << endl;
    }
}

// ================== RẮN ==================
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
        // FIX: xóa đuôi.
        gotoxy(A[DoDai - 1].x, A[DoDai - 1].y);
        cout << " ";

        for (int i = DoDai - 1; i > 0; i--){
            A[i] = A[i - 1];
        }

        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;
    }
};

// ================== THUA ==================
bool KiemTraThua(const CONRAN &r){
    // đụng thân
    for(int i = 1; i < r.DoDai; i++){
        if(r.A[i].x == r.A[0].x && r.A[i].y == r.A[0].y)
            return false;
    }

    // đụng tường
    if(r.A[0].x == 0 || r.A[0].x == 39 ||
       r.A[0].y == 0 || r.A[0].y == 19)
        return false;

    return true;
}

// ================== GOTOXY ==================
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

// ================== MAIN ==================
int main(){

    AnConTro();
    CONRAN r;
    int Huong = 0;
    int i = 0;

    char t;
    int thucAnX, thucAnY;
    int diem = 0;

    srand(time(0));
    khoiTaoThucAn(thucAnX, thucAnY);

    while (KiemTraThua(r)){

        if (kbhit()){
            t = getch();
            if (t == 'a' && Huong != 0) Huong = 2;
            if (t == 'w' && Huong != 1) Huong = 3;
            if (t == 'd' && Huong != 2) Huong = 0;
            if (t == 's' && Huong != 3) Huong = 1;
        }

        gotoxy(0,0);

        r.DiChuyen(Huong);

        if (kiemTraAnMoi(r.A[0].x, r.A[0].y, thucAnX, thucAnY, diem)){
            r.DoDai++;

#ifdef _WIN32
            if(i < 250) i += 10;
#else
            if(i < 250000) i += 10000;
#endif
        }

        VeKhung();

        gotoxy(thucAnX, thucAnY);
        cout << "*";

        r.Ve();

        gotoxy(0, 21);
        cout << "Diem: " << diem;

#ifdef _WIN32
        int delay = 300 - i;
        if (delay < 50) delay = 50;
        Sleep(delay);
#else
        int delay = 300000 - i;
        if (delay < 50000) delay = 50000;
        usleep(delay);
#endif
    }

    cout << "\nGame over";
    return 0;
}

#ifndef _WIN32
// giữ nguyên phần này
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