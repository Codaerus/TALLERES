#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //Para el system(cls)

#define WIDTH 20 //Ancho de la pantalla

int main(){
	int x = WIDTH/2; //posición inicial
	char input;
	while(1){
			system("cls");
			for(int i=0; i<WIDTH;i++){
				if(i == x){
					printf("O");
				}
				else{
					printf("-");
				}
				
			}
			printf("\n");
			if(_kbhit()){
				input = _getch();
				if(input == 'a' && x>0) x--;
				if(input == 'd' && x<WIDTH-1) x++;
			}	
	}

	return 0;
}
