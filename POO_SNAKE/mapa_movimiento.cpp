#include <iostream>
#include <conio.h>
#include <windows.h>

// Clase para dibujar el mapa
class Mapa {
private:
    int ancho, alto;

    void gotoxy(int x, int y) {
        COORD coord = {(short)x, (short)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Mapa(int w = 20, int h = 20) : ancho(w), alto(h) {}

    void Mostrar() {
        gotoxy(0, 0);
        for (int i = 0; i < ancho + 2; i++) std::cout << "#";
        std::cout << "\n";

        for (int i = 0; i < alto; i++) {
            std::cout << "#";
            for (int j = 0; j < ancho; j++) {
                std::cout << " ";
            }
            std::cout << "#\n";
        }

        for (int i = 0; i < ancho + 2; i++) std::cout << "#";
        std::cout << std::endl;
    }
};

// Clase para el personaje
class Personaje {
private:
    int x, y;
    char simbolo;

    void gotoxy(int x, int y) {
        COORD coord = {(short)x, (short)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Personaje(int posX = 10, int posY = 10, char simbolo = '*')
        : x(posX), y(posY), simbolo(simbolo) {}

    void Mostrar() {
        gotoxy(x, y);
        std::cout << simbolo;
    }

    void Mover(int dx, int dy) {
        gotoxy(x, y);
        std::cout << " ";
        x += dx;
        y += dy;
        Mostrar();
    }
};

// Oculta el cursor
void ocultarCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

int main() {
    ocultarCursor();

    Mapa mapa(20, 10);
    mapa.Mostrar();

    Personaje jugador(10, 5);
    jugador.Mostrar();

    bool jugando = true;
    while (jugando) {
        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'w': jugador.Mover(0, -1); break;
                case 's': jugador.Mover(0, 1); break;
                case 'a': jugador.Mover(-1, 0); break;
                case 'd': jugador.Mover(1, 0); break;
                case 'x': jugando = false; break;
            }
        }
        Sleep(50);
    }

    return 0;
}
