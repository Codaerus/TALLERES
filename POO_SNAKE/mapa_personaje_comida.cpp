#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

class Mapa {
private:
    int ancho, alto;
public:
    Mapa(int w, int h) : ancho(w), alto(h) {}

    void Mostrar() const {
        gotoxy(0, 0);
        // Línea superior
        for (int i = 0; i < ancho + 2; i++) cout << "#";
        cout << "\n";

        // Líneas con bordes laterales
        for (int i = 0; i < alto; i++) {
            cout << "#";
            for (int j = 0; j < ancho; j++) cout << " ";
            cout << "#\n";
        }

        // Línea inferior
        for (int i = 0; i < ancho + 2; i++) cout << "#";
        cout << endl;
    }

    int getAncho() const { return ancho; }
    int getAlto() const { return alto; }
};

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

class Personaje {
private:
    int x, y;
    char simbolo;

public:
    Personaje(int posX, int posY, char s = '*') : x(posX), y(posY), simbolo(s) {}

    void Mostrar() const {
        gotoxy(x, y);
        cout << simbolo;
    }

    void Borrar() const {
        gotoxy(x, y);
        cout << " ";
    }

    void Mover(int dx, int dy) {
        Borrar();
        x += dx;
        y += dy;
        Mostrar();
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

int main() {
    srand((unsigned)time(0));
    ocultarCursor();

    Mapa mapa(40, 20);
    mapa.Mostrar();

    Fruta fruta(mapa.getAncho(), mapa.getAlto());
    fruta.Mostrar();

    Personaje jugador(10, 10);
    jugador.Mostrar();

    int dx = 0, dy = 0;

    while (true) {
        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'w': dx = 0; dy = -1; break;
                case 's': dx = 0; dy = 1; break;
                case 'a': dx = -1; dy = 0; break;
                case 'd': dx = 1; dy = 0; break;
                case 'x': return 0;  // salir
            }
        }

        jugador.Mover(dx, dy);

        // Si toca la fruta, genera nueva
        if (jugador.getX() == fruta.getX() && jugador.getY() == fruta.getY()) {
            fruta.GenerarNueva();
            fruta.Mostrar();
        }

        Sleep(150);
    }

    return 0;
}
