#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //Para el system(cls)
#include <unistd.h>
#define WIDTH 20 //Ancho de la pantalla
#define HEIGHT 10 //Alto

int main(){
	int x = WIDTH/2, y = HEIGHT/2; //posición inicial
	char input;
	while(1){
			system("cls");
			for(int i=0; i<HEIGHT; i++){
				for(int j=0; j<WIDTH;j++){
					if(i == y && j == x ){
						printf("O");
					}
					else{
						printf("-");
					}
					
				}
				printf("\n");
			}
			if(_kbhit()){
				input = _getch();
				switch(input){
					case 'w': if(y>0) y--;break; //Arriba
					case 's': if(y<HEIGHT-1) y++;break; //Abajo
					case 'a': if(x>0) x--;break; //Izquierda
					case 'd': if(x<WIDTH-1) x++;break;//Derecha
				}
			}	
			usleep(100000);
	}

	return 0;
}
