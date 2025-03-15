#include <stdio.h>

#define WIDTH 20
#define HEIGHT 10

void drawFrame(){
	for(int i = 0; i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(i ==0||i==HEIGHT-1||j==0||j== WIDTH-1)
				{
					printf("#");
				}
			else{
				printf(" ");
				}
		}
		printf("\n");
	}
}

int main(){
	drawFrame();
	return 0;
}

/*
             (i,j)
##########  (0,0)(0,1)...(0,WIDTH-1)
#        #  (1,0)(1,1)
#        #
#   O    #
#        #
#        #
##########
*/
