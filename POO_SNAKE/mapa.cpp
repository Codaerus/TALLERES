#include <iostream>
#include <windows.h>

class Mapa {
private:
    int ancho, alto;

    void gotoxy(int x, int y) {
        COORD coord = { (short)x, (short)y };
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

int main() {
    Mapa mapa(20, 20);
    mapa.Mostrar();
    system("pause");
    return 0;
}
