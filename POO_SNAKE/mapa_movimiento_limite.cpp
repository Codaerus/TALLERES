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
    Mapa(int w = 20, int h = 10) : ancho(w), alto(h) {}

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

    // Método corregido: ahora es const
    bool DentroLimites(int x, int y) const {
        return (x > 0 && x <= ancho && y > 0 && y <= alto);
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
    Personaje(int posX = 10, int posY = 5, char simbolo = '*')
        : x(posX), y(posY), simbolo(simbolo) {}

    void Mostrar() {
        gotoxy(x, y);
        std::cout << simbolo;
    }

    void Mover(int dx, int dy, const Mapa& mapa) {
        int nuevaX = x + dx;
        int nuevaY = y + dy;

        // Verificar si la nueva posición está dentro de los límites del mapa
        if (mapa.DentroLimites(nuevaX, nuevaY)) {
            gotoxy(x, y);
            std::cout << " ";
            x = nuevaX;
            y = nuevaY;
            Mostrar();
        }
    }
};

// Oculta el cursor en consola
void ocultarCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

int main() {
    ocultarCursor();

    Mapa mapa(20, 10); // Mapa de 20x10 (área interna)
    mapa.Mostrar();

    Personaje jugador(10, 5); // Posición inicial del personaje
    jugador.Mostrar();

    bool jugando = true;
    while (jugando) {
        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'w': jugador.Mover(0, -1, mapa); break;
                case 's': jugador.Mover(0, 1, mapa); break;
                case 'a': jugador.Mover(-1, 0, mapa); break;
                case 'd': jugador.Mover(1, 0, mapa); break;
                case 'x': jugando = false; break;
            }
        }
        Sleep(50);
    }

    return 0;
}
