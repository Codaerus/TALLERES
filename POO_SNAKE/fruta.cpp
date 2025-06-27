#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Fruta {
private:
    int x, y;
    int maxX, maxY;

public:
    Fruta(int maxX, int maxY) : maxX(maxX), maxY(maxY) {
        GenerarNueva();
    }

    void GenerarNueva() {
        x = rand() % maxX + 1;
        y = rand() % maxY + 1;
    }

    void Mostrar() const {
        gotoxy(x, y);
        cout << "F";
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

int main() {
    srand((unsigned)time(0));

    Fruta fruta(40, 20);
    fruta.Mostrar();

    // Solo para que no se cierre inmediatamente
    cin.get();

    return 0;
}
