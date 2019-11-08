#include <string.h>
#include "spinv.h"
#include "lib_lista.h"

void initsprintsaliens (int **c_aliens) {
	
	strcpy (c_aliens[1],ALIEN11);	
	strcpy (c_aliens[2],ALIEN12);	
	strcpy (c_aliens[3],ALIEN13);	
	strcpy (c_aliens[4],ALIEN112);	
	strcpy (c_aliens[5],ALIEN122);	
	strcpy (c_aliens[6],ALIEN132);

	strcpy (c_aliens[7],ALIEN21);	
	strcpy (c_aliens[8],ALIEN22);	
	strcpy (c_aliens[9],ALIEN23);	
	strcpy (c_aliens[10],ALIEN212);	
	strcpy (c_aliens[11],ALIEN222);	
	strcpy (c_aliens[12],ALIEN232);	

	strcpy (c_aliens[13],ALIEN31);	
	strcpy (c_aliens[14],ALIEN32);	
	strcpy (c_aliens[15],ALIEN33);	
	strcpy (c_aliens[16],ALIEN312);	
	strcpy (c_aliens[17],ALIEN322);	
	strcpy (c_aliens[18],ALIEN332);	
}

void inicializa_aliens (t_listAliens *aliens) {
	
	initaliens (aliens);

	int i,j;

	for (i = 0; i < LINHASALIENS; i++)
		for (j = 0; j < LINHASCOLUNAS; j++)
			insalienslista (aliens,i,j);
}
void prntaliens (t_aliens);
