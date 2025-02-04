#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define SOL 75
#define SAG 77
#define YUKARI 72
#define ASAGI 80

#define SOLSINIR 1
#define SAGSINIR 20
#define ALTSINIR 10
#define USTSINIR 2

void gotoxy(int x, int y); // cursor konumu
void hidecursor();
int yemcagir, mayinla;
int sayix, sayiy, i;
int karx = 10, kary = 6; // KARAKTERIMIZIN BASLANGIC KONUMU
int skor, can = 1;
char harita[ALTSINIR][SAGSINIR]; // HAREKETLERIMIZI DIZIDE TUTUYORUZ
int cikis;
using namespace std;

class sinir_ciz {
public:
    sinir_ciz() // OYUN ALANIMIZI CIZIYORUZ
    {
        int x, y;
        cout << std::endl;
        for (y = 0; y < ALTSINIR + 1; y++)
        {
            for (x = 0; x < SAGSINIR + 1; x++)
            {
                if (x == 0 && y == 0)
                    cout << (char)201;
                else if (x == SAGSINIR && y == 0)
                    cout << (char)187;
                else if (y == 0)
                    cout << (char)205;
                else if (y == ALTSINIR && x == 0)
                    cout << (char)200;
                else if (x == 0 && y > 0)
                    cout << (char)186;
                else if (y == ALTSINIR && x == SAGSINIR)
                    cout << (char)188;
                else if (x == SAGSINIR)
                    cout << (char)186;
                else if (y == ALTSINIR)
                    cout << (char)205;
                else
                    cout << " ";
            }
            cout << std::endl;
        }
    }
};

class yemle {
public:
    yemle() // RASGELE ALTIN ATIYORUZ
    {
        int x, y;
        sayix = USTSINIR + rand() % ALTSINIR;
        sayiy = SOLSINIR + rand() % SAGSINIR;
        if (sayiy >= SAGSINIR)
            --sayiy;
        if (sayix >= ALTSINIR)
            --sayix;
        harita[sayix][sayiy] = '*';
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { sayiy, sayix };
        SetConsoleCursorPosition(hConsole, pos);
        WriteConsole(hConsole, "*", 1, NULL, NULL);
    }
};

class kontrol {
public:
    kontrol()
    {
        if (harita[kary][karx] == '*')
        {
            harita[kary][karx] = ' ';
            ++skor;
            gotoxy(SAGSINIR + 5, 5);
            cout << "SKOR= " << skor;
        }

        if (harita[kary][karx] == '#') // Karakter dokununca yanar
        {
            harita[kary][karx] = ' ';
            --can;
            gotoxy(SAGSINIR + 5, 3);
            cout << "CAN= " << can;
        }

        if (can == 0)
        {
            gotoxy(SOLSINIR + 5, ALTSINIR / 2);
            cout << "GAME OVER";
            
        }
    }
};

class mayin {
public:
    mayin() // RASGELE MAYIN ATIYORUZ
    {
        int x, y;
        sayix = USTSINIR + rand() % ALTSINIR;
        sayiy = SOLSINIR + rand() % SAGSINIR;
        if (sayiy >= SAGSINIR)
            --sayiy;
        if (sayix >= ALTSINIR)
            --sayix;
        harita[sayix][sayiy] = '#'; // kontrol icin diziye atiyoruz
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { sayiy, sayix };
        SetConsoleCursorPosition(hConsole, pos);
        WriteConsole(hConsole, "# ", 1, NULL, NULL); // mayindan sonra 1 karekter
    }
};

void gotoxy(int x, int y)
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void hidecursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int main()
{
    cout << "   **MAYIN TARLASI** ";
    sinir_ciz();

    gotoxy(SAGSINIR + 5, 5);
    cout << "SKOR= " << skor;

    gotoxy(SAGSINIR + 5, 3);
    cout << "CAN= " << can;

    gotoxy(SAGSINIR + 5, USTSINIR + 5);
    //cout << "'Hareket Ettikce Altinlar Artacaktir!'";

    gotoxy(SAGSINIR + 5, USTSINIR + 7);
    //cout << "'Mayinlara Basmadan Altinlari Topla :)'";

    gotoxy(ALTSINIR - 9, SAGSINIR - 8);
    cout << "|* ALTIN | # MAYIN| \n";

    int x = 15, y = 10, ch1, ch2;
    hidecursor();

    gotoxy(karx, kary);
    cout << "X";

    ch1 = _getch();
    ch2 = 0;

    srand(time(NULL));
    if (ch1 == 0xE0)
    {
        while (ch2 = _getch())
        {
            if (ch2 == 'X')
                exit(0);
            if (ch2 == SOL)
            {
                if (karx > SOLSINIR)
                {
                    gotoxy(--karx, kary);
                    cout << "X";
                    gotoxy(karx + 1, kary);
                    cout << " ";
                }
            }
            yemcagir = 1 + rand() % 45; // Rasgele Altin Atýyoruz
            if (yemcagir == 40 || yemcagir == 31)
                yemle();
            mayinla = 1 + rand() % 10; // Rasgele Mayin Atýyoruz
            if (mayinla == 1)
                mayin();
            if (ch2 == SAG)
            {
                if (karx + 1 < SAGSINIR)
                {
                    gotoxy(++karx, kary);
                    cout << "X";
                    gotoxy(karx - 1, kary);
                    cout << " ";
                }
            }
            if (ch2 == YUKARI)
            {
                if (kary > USTSINIR)
                {
                    gotoxy(karx, --kary);
                    cout << "X";
                    gotoxy(karx, kary + 1);
                    cout << " ";
                }
            }
            if (ch2 == ASAGI)
            {
                if (kary < ALTSINIR)
                {
                    gotoxy(karx, ++kary);
                    cout << "X";
                    gotoxy(karx, kary - 1);
                    cout << " ";
                }
            }
            kontrol();
        }
    }
    _getch();
}

