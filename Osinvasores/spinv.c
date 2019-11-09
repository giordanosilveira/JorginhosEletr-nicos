#include <string.h>
#include "spinv.h"
void initsprintsaliens (char **c_aliens) {
	
	strcpy (c_aliens[0],ALIEN11);	
	strcpy (c_aliens[1],ALIEN12);	
	strcpy (c_aliens[2],ALIEN13);	
	strcpy (c_aliens[3],ALIEN112);	
	strcpy (c_aliens[4],ALIEN122);	
	strcpy (c_aliens[5],ALIEN132);

	strcpy (c_aliens[6],ALIEN21);	
	strcpy (c_aliens[7],ALIEN22);	
	strcpy (c_aliens[8],ALIEN23);	
	strcpy (c_aliens[9],ALIEN212);	
	strcpy (c_aliens[10],ALIEN222);	
	strcpy (c_aliens[11],ALIEN232);	

	strcpy (c_aliens[12],ALIEN31);	
	strcpy (c_aliens[13],ALIEN32);	
	strcpy (c_aliens[14],ALIEN33);	
	strcpy (c_aliens[15],ALIEN312);	
	strcpy (c_aliens[16],ALIEN322);	
	strcpy (c_aliens[17],ALIEN332);	
}

void inicializa_aliens (t_listAliens *aliens) {
	
	initaliens (aliens);

	int i,j;

	for (i = 0; i < LINHASDALIENS; i++)
		for (j = 0; j < COLUNASDALIENS; j++)
			insalienslista (aliens,i,j);
}
void prntaliens (t_listAliens *al,char **corposA) {

	int k,versao,pos;
	t_alien *et;
	
	et = al->ini->prox;
	k = 0;
	versao = 0; /*versao que é para imprimir do alien*/

	while (k < QNTET) {
		
		pos = (et->pos.x + 1)/2;		/*essa conta serve para pegar os sprit desejado do alien*/
		if (et->status == VIVO) {
			if (versao) { /*se a versao do alien for 1 ele entra aqui*/ 
				mvprintw (et->pos.x,et->pos.y,corposA[pos*6+3]);	
				mvprintw (et->pos.x+1,et->pos.y+1,corposA[pos*6+4]);
				mvprintw (et->pos.x+2,et->pos.y+2,corposA[pos*6+5]);
			}
			else {
				
				mvprintw (et->pos.x,et->pos.y,corposA[pos*6]);
				mvprintw (et->pos.x+1,et->pos.y+1,corposA[pos*6+1]);
				mvprintw (et->pos.x+2,et->pos.y+2,corposA[pos*6+2]);
			}
	
		}
		versao = (versao+1) % 2;
		et = et->prox;
		k = k+1;
	}
}
