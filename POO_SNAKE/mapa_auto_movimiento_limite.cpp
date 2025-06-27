#include <iostream>
#include <conio.h>
#include <windows.h>

// Clase para dibujar el mapa
class Mapa {
private:
    int ancho, alto;

    void gotoxy(int x, int y) const {
        COORD coord = {(short)x, (short)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Mapa(int w = 20, int h = 10) : ancho(w), alto(h) {}

    void Mostrar() const {
        gotoxy(0, 0);
        for (int i = 0; i < ancho + 2; i++) std::cout << "#";
        std::cout << "\n";

        for (int i = 0; i < alto; i++) {
            std::cout << "#";
            for (int j = 0; j < ancho; j++) std::cout << " ";
            std::cout << "#\n";
        }

        for (int i = 0; i < ancho + 2; i++) std::cout << "#";
        std::cout << std::endl;
    }

    bool DentroLimites(int x, int y) const {
        return (x > 0 && x <= ancho && y > 0 && y <= alto);
    }
};

// Clase para el personaje
class Personaje {
private:
    int x, y;
    char simbolo;

    void gotoxy(int x, int y) const {
        COORD coord = {(short)x, (short)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    Personaje(int posX = 10, int posY = 5, char simbolo = '*')
        : x(posX), y(posY), simbolo(simbolo) {}

    void Mostrar() const {
        gotoxy(x, y);
        std::cout << simbolo;
    }

    void Borrar() const {
        gotoxy(x, y);
        std::cout << " ";
    }

    bool Mover(int dx, int dy, const Mapa& mapa) {
        int nuevaX = x + dx;
        int nuevaY = y + dy;

        if (mapa.DentroLimites(nuevaX, nuevaY)) {
            Borrar();
            x = nuevaX;
            y = nuevaY;
            Mostrar();
            return true;
        } else {
            return false; // Colisión con el borde
        }
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

    int dx = 1, dy = 0; // dirección inicial: derecha
    bool jugando = true;

    while (jugando) {
        // Cambiar dirección si se presiona tecla
        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'w': dx = 0; dy = -1; break;
                case 's': dx = 0; dy = 1; break;
                case 'a': dx = -1; dy = 0; break;
                case 'd': dx = 1; dy = 0; break;
                case 'x': jugando = false; break; // salir manual
            }
        }

        // Movimiento automático
        if (!jugador.Mover(dx, dy, mapa)) {
            // Si choca con borde
            std::cout << "\n?? Game Over! Tocaste un borde.\n";
            jugando = false;
        }

        Sleep(150); // velocidad del snake
    }

    return 0;
}
