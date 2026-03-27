#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <locale>
#include <ctime>
    //Hải quan hệ điều hành
#ifdef _WIN32
    // Nếu là Windows thì nạp thư viện này
    #include <windows.h>
    #include <conio.h>
#else
    // Nếu là Mac/Linux thì nạp thư viện này
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

#define WIDTH 40
#define HEIGHT 20

using namespace std;

void gotoxy( int column, int line );
#ifndef _WIN32
int kbhit(void);
int getch(void);
#endif
struct Point{
    int x,y;
};
class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    Point food;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }
    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"X";
        }
    }
    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }
    void TaoThucAn(){
    food.x = rand() % (WIDTH-1) + 1;
    food.y = rand() % (HEIGHT-1) + 1;
    }
    void VeThucAn(){
    gotoxy(food.x, food.y);
    cout<<"O";
    }
    void TangDoDai(){
        if(A[0].x==food.x&&A[0].y==food.y) {
            DoDai++;
            TaoThucAn();
        }
    }
    void VeKhung(){
        for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {

            // Góc
            if(i == 0 && j == 0) cout << "o";
            else if(i == 0 && j == WIDTH - 1) cout << "o";
            else if(i == HEIGHT - 1 && j == 0) cout << "o";
            else if(i == HEIGHT - 1 && j == WIDTH - 1) cout << "o";

            // Cạnh trên & dưới
            else if(i == 0 || i == HEIGHT - 1) cout << "-";

            // Cạnh trái & phải
            else if(j == 0 || j == WIDTH - 1) cout << "|";

            // Bên trong
            else cout << " ";
        }
        cout << endl;
    }
    }
};

void gotoxy(int column, int line)
{
    #ifdef _WIN32
    // Code cho Windows
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    // Code cho Mac
    printf("\033[%d;%dH", line, column);
#endif
}



int main()
{
    srand(time(0));
    CONRAN r;
    int Huong = 0;
    char t;
    int width = 40;
    int height = 20;

    r.TaoThucAn();

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='s') Huong = 1;
        }

        // Trạm kiểm soát lệnh xóa màn hình
        #ifdef _WIN32
            system("cls");
        #else
            systemwwww("clear");
        #endif

        r.VeKhung();
        r.VeThucAn();
        r.Ve();
        r.DiChuyen(Huong);
        r.TangDoDai();

        // Trạm kiểm soát lệnh delay thời gian
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
