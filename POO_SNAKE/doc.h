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
/*
srand
Descripción: Inicializa la semilla para la generación de números pseudoaleatorios con rand().
*/
void srand(unsigned int seed);
/*
rand
Descripción: Genera un número pseudoaleatorio entero entre 0 y RAND_MAX
*/
int rand(void);
/*
cin.get
Descripción: Lee un carácter desde la entrada estándar (normalmente el teclado). Se usa comúnmente para esperar una entrada del usuario, como pulsar Enter.
*/
int std::istream::get();
