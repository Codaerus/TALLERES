/*COORD
Estructura que representa una posición (x, y) en la consola de Windows.
*/
typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD;
/*
GetStdHandle
Descripción: Función que obtiene el identificador (handle) de un dispositivo estándar, como la consola de salida.
*/
HANDLE GetStdHandle(DWORD nStdHandle);
/*
SetConsoleCursorPosition
Descripción: Función que mueve el cursor de la consola a la posición dada por una estructura COORD.
*/
BOOL SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD dwCursorPosition);

