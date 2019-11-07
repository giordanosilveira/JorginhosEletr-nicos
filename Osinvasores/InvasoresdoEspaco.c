#include "spinv.h" 
int main () {

	int **corposaliens,i;
	corposaliens = (int **)malloc(sizeof(int*)*QNTCORPOS);
	for (i = 0; i < QNTCORPOS; i++) {
		corposaliens[i] = (int *)malloc(sizeof(int)*TAMET);
	}
	initspritsalien(corposaliens); /*inicializa os corpos dos aliens*/
	
	/*For the time being, that's all folks*/



































}
