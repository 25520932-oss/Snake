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

<<<<<<< HEAD
//An con tro chuot
#ifdef _WIN32
void AnConTro(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;  // Ẩn con trỏ
    SetConsoleCursorInfo(hOut, &cursorInfo);
}
#endif
#ifndef _WIN32
void AnConTro(){
    printf("\033[?25l");  // Ẩn cursor
}
#endif

=======
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
void gotoxy(int column, int line);

#ifndef _WIN32
int kbhit(void);
int getch(void);
#endif

// Hàm tạo tọa độ ngẫu nhiên cho thức ăn
void khoiTaoThucAn(int &thucAnX, int &thucAnY) {
<<<<<<< HEAD
    thucAnX = rand() % 39 ;
    if(thucAnX==0) thucAnX++;
    thucAnY = rand() % 19 ;
    if(thucAnY==0) thucAnY++;
=======
    thucAnX = rand() % 40 + 5;
    thucAnY = rand() % 15 + 5;
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
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

<<<<<<< HEAD
// Hàm để vẽ khung trò chơi
void VeKhung(){
    for(int i = 0; i < 20; i++) {
    for(int j = 0; j < 40; j++) {

        // Góc
        if(i == 0 && j == 0) cout << "o";
        else if(i == 0 && j == 40 - 1) cout << "o";
        else if(i == 20 - 1 && j == 0) cout << "o";
        else if(i == 20 - 1 && j == 40 - 1) cout << "o";

        // Cạnh trên & dưới
        else if(i == 0 || i == 20 - 1) cout << "-";

        // Cạnh trái & phải
        else if(j == 0 || j == 40 - 1) cout << "|";

        // Bên trong
        else cout << " ";
    }
    cout << endl;
}
}

=======
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
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

<<<<<<< HEAD
//Hàm kiểm tra thua
bool KiemTraThua(CONRAN r){
    //Kiểm tra đụng thân
    for(int i=5;i<r.DoDai;i++){
        if(r.A[i].x==r.A[0].x&&r.A[i].y==r.A[0].y) return 0;
    }
    //Kiểm tra đụng tường
    if(r.A[0].x==0||r.A[0].x==39||r.A[0].y==0||r.A[0].y==19) return 0;
    return 1;
}

=======
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
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
<<<<<<< HEAD
    AnConTro();
    CONRAN r;
    int Huong = 0;
    int i=0;//tang toc do game
=======
    CONRAN r;
    int Huong = 0;
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
    char t;
    //khai bao va chay ham tao thuc an
    int thucAnX, thucAnY;
    int diem = 0;

    srand(time (0));
    khoiTaoThucAn(thucAnX,thucAnY);

<<<<<<< HEAD
    while (KiemTraThua(r)){

        if (kbhit()){
            t = getch();
            if (t == 'a' && Huong != 0) Huong = 2; // tranh dao chieu
            if (t == 'w' && Huong != 1) Huong = 3;
            if (t == 'd' && Huong != 2) Huong = 0;
            if (t == 's' && Huong != 3) Huong = 1; // đổi lại s cho chuẩn WASD
        }
        //thay cho clear man hinh
        gotoxy(0,0);
//clear man hinh lam khung bi nhap nhay
/*#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif*/
=======
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
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
        r.DiChuyen(Huong);

        // kiểm tra ăn mồi
        if (kiemTraAnMoi(r.A[0].x, r.A[0].y, thucAnX, thucAnY, diem)){
            r.DoDai++;
<<<<<<< HEAD
            //Tang toc do
            #ifdef _WIN32
            if(i<200)
            i+=10;
            #else
            if(i<200000)
            i+=10000;
            #endif // _WIN32
        }

        // vẽ khung
        VeKhung();

=======
        }

>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
        // vẽ mồi
        gotoxy(thucAnX, thucAnY);
        cout << "*";

        // vẽ rắn
        r.Ve();

        // in điểm
<<<<<<< HEAD
        gotoxy(0,21);
=======
        gotoxy(0, 0);
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
        cout << "Diem: " << diem;


#ifdef _WIN32
<<<<<<< HEAD
        Sleep(300-i);
#else
        usleep(300000-i);
#endif
    }
    cout<<"\nGame over";
=======
        Sleep(300);
#else
        usleep(300000);
#endif
    }
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706

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

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 07a415a8406920f28206eb7a4324908feb76f706
