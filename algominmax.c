#include "morpion.h"
int min_max (char *tab,joueur **js,char j)
{
    int score=-2,i,deplace=-1;
	 int score_actuel;

    if(statut_jeu(tab, js)==1 && j==js[0]->symbole)
    	return 1;
    if(statut_jeu(tab,js)==2 && j==js[1]->symbole)
    	return 1;
    if((statut_jeu(tab,js)==1 && j==js[1]->symbole) || (statut_jeu(tab, js)==2 && j==js[0]->symbole))
    	return -1;

	
	for (i=0;i<N;i++)
	{
	   if(tab[i]=='-')
	     {

	        tab[i]=j;
	        if(j==js[0]->symbole)
	           score_actuel=-min_max(tab,js,js[1]->symbole);
	        else
	           score_actuel=-min_max(tab,js,js[0]->symbole);
	        if(score_actuel>score)
	          {
	              score=score_actuel;
	              deplace=i;
	          }
	        tab[i]='-';
	     }
	}

	if(deplace==-1)
	    return 0;
        
        return score;

}

