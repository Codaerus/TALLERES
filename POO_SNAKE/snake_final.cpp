#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
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

    void Mover(int nx, int ny) {
        Borrar();
        x = nx;
        y = ny;
        Mostrar();
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

void mostrarScore(int score, int yPos) {
    gotoxy(0, yPos);
    cout << "Frutas comidas: " << score << "    ";
}

void mostrarGameOver(int yPos, int score) {
    gotoxy(0, yPos);
    cout << "Game Over! Frutas comidas: " << score << "     " << endl;
}

int main() {
    srand((unsigned)time(0));
    ocultarCursor();

    Mapa mapa(40, 20);
    mapa.Mostrar();

    Fruta fruta(mapa.getAncho(), mapa.getAlto());
    fruta.Mostrar();

    Personaje jugador(10, 10);
    jugador.Mostrar();

    vector<int> colaX;
    vector<int> colaY;

    int dx = 0, dy = 0;
    int score = 0;
    bool gameOver = false;

    mostrarScore(score, mapa.getAlto() + 3);

    while (!gameOver) {
        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'w': if (dy != 1) { dx = 0; dy = -1; } break;
                case 's': if (dy != -1) { dx = 0; dy = 1; } break;
                case 'a': if (dx != 1) { dx = -1; dy = 0; } break;
                case 'd': if (dx != -1) { dx = 1; dy = 0; } break;
                case 'x': gameOver = true; break;
            }
        }

        int nuevoX = jugador.getX() + dx;
        int nuevoY = jugador.getY() + dy;

        // Chequear colisión con bordes
        if (nuevoX < 1 || nuevoX > mapa.getAncho() || nuevoY < 1 || nuevoY > mapa.getAlto()) {
            gameOver = true;
            continue;
        }

        // Mover cola: borrar última posición de cola
        if (!colaX.empty()) {
            gotoxy(colaX.back(), colaY.back());
            cout << " ";
            // Mover cola hacia adelante
            for (int i = (int)colaX.size() - 1; i > 0; i--) {
                colaX[i] = colaX[i - 1];
                colaY[i] = colaY[i - 1];
            }
            colaX[0] = jugador.getX();
            colaY[0] = jugador.getY();
        }

        // Actualizar posición de jugador
        jugador.Mover(nuevoX, nuevoY);

        // Dibujar cola
        for (size_t i = 0; i < colaX.size(); i++) {
            gotoxy(colaX[i], colaY[i]);
            cout << "o";
        }

        // Chequear colisión con cola
        for (size_t i = 0; i < colaX.size(); i++) {
            if (colaX[i] == nuevoX && colaY[i] == nuevoY) {
                gameOver = true;
                break;
            }
        }

        // Comer fruta
        if (jugador.getX() == fruta.getX() && jugador.getY() == fruta.getY()) {
            score++;
            fruta.GenerarNueva();
            fruta.Mostrar();
            mostrarScore(score, mapa.getAlto() + 3);

            // Añadir nuevo segmento cola (posicionar temporalmente fuera del mapa, se actualizará en próximo ciclo)
            colaX.push_back(-1);
            colaY.push_back(-1);
        }

        Sleep(150);
    }

    mostrarGameOver(mapa.getAlto() + 5, score);
    system("pause");
    return 0;
}
