#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    const int width = 20;
    const int height = 20;
    int x, y;                // Posición de la cabeza
    int fruitX, fruitY;
    int score;
    int tailLength;
    vector<int> tailX, tailY;
    bool gameOver;
    Direction dir;

    // Oculta el cursor en consola
    void HideCursor() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hOut, &cursorInfo);
    }

    // Mueve el cursor a una posición sin borrar pantalla
    void gotoxy(int x, int y) {
        COORD coord = { (short)x, (short)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

public:
    SnakeGame() {
        srand((unsigned)time(0));
        Setup();
        HideCursor();
    }

    void Setup() {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        tailLength = 0;
        tailX.clear();
        tailY.clear();
    }

    void Draw() {
        gotoxy(0, 0);
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "#";

                if (i == y && j == x)
                    cout << "*"; // Cabeza
                else if (i == fruitY && j == fruitX)
                    cout << "F"; // Fruta
                else {
                    bool printed = false;
                    for (int k = 0; k < tailLength; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << "o";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) cout << " ";
                }

                if (j == width - 1) cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << "\nScore: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': case 'A': if (dir != RIGHT) dir = LEFT; break;
                case 'd': case 'D': if (dir != LEFT)  dir = RIGHT; break;
                case 'w': case 'W': if (dir != DOWN)  dir = UP; break;
                case 's': case 'S': if (dir != UP)    dir = DOWN; break;
                case 'x': case 'X': gameOver = true; break;
            }
        }
    }

    void Logic() {
        int prevX = x, prevY = y;
        int prev2X, prev2Y;

        if (tailLength > 0) {
            prev2X = tailX[0];
            prev2Y = tailY[0];
            tailX[0] = prevX;
            tailY[0] = prevY;

            for (int i = 1; i < tailLength; i++) {
                prevX = tailX[i];
                prevY = tailY[i];
                tailX[i] = prev2X;
                tailY[i] = prev2Y;
                prev2X = prevX;
                prev2Y = prevY;
            }
        }

        switch (dir) {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case UP:    y--; break;
            case DOWN:  y++; break;
            default: break;
        }

        // Colisiones
        if (x < 0 || x >= width || y < 0 || y >= height)
            gameOver = true;

        for (int i = 0; i < tailLength; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        // Comer fruta
        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            tailLength++;
            tailX.push_back(0);
            tailY.push_back(0);
        }
    }

    void Run() {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100); // Velocidad
        }

        gotoxy(0, height + 3);
        cout << "Game Over! Score: " << score << endl;
        system("pause");
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}
