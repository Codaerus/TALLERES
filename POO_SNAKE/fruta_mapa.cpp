#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

        // Líneas intermedias con bordes laterales
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

int main() {
    srand((unsigned)time(0));

    Mapa mapa(40, 20);
    mapa.Mostrar();

    Fruta fruta(mapa.getAncho(), mapa.getAlto());
    fruta.Mostrar();

    // Pausa para ver el resultado
    cin.get();

    return 0;
}
