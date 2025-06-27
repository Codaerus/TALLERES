#include <iostream>
#include <conio.h>    // _kbhit(), _getch()
#include <windows.h>  // gotoxy, Sleep

// Clase Personaje
class Personaje {
private:
    int x, y;
    char simbolo;

    void gotoxy(int x, int y) {
        COORD coord = { (short)x, (short)y };
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
        // Borra símbolo anterior
        gotoxy(x, y);
        std::cout << " ";
        // Actualiza posición
        x += dx;
        y += dy;
        Mostrar();
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

// Función para ocultar el cursor
void ocultarCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Función principal
int main() {
    ocultarCursor();

    Personaje jugador(10, 10, '*');
    jugador.Mostrar();

    bool jugando = true;
    while (jugando) {
        if (_kbhit()) {
            char tecla = _getch();

            switch (tecla) {
                case 'w': jugador.Mover(0, -1); break;
                case 's': jugador.Mover(0,  1); break;
                case 'a': jugador.Mover(-1, 0); break;
                case 'd': jugador.Mover(1,  0); break;
                case 'x': jugando = false; break; // salir con X
            }
        }
        Sleep(50); // Controla la velocidad de lectura
    }

    return 0;
}
