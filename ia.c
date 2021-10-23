#include "morpion.h"



joueur** init_joueur_ia_perso()
{
	joueur *j1 = creer_joueur();
	joueur *j2 = creer_joueur();
	joueur **js = malloc(sizeof(joueur*)*2);
	char sym[2];

	if(!js)
		exit(0);

	printf("Joueur 1\n");
	printf("Entrez votre nom : ");
	read_c(j1->nom, 20);

	do
	{
		printf("Choisissez votre symbole : (caratere alphabetique) ");
		read_c(sym, 2);

	}while(si_alpha(sym) == 0);

	if('a'<=sym[0] && sym[0] <= 'z')
	{
		j1->symbole = sym[0] - ('a' - 'A');
	}
	else
	{
		j1->symbole = sym[0];
	}

	choix_couleur_joueur(j1);
	#ifdef _WIN32
	printf("Joueur 1: %s(", j1->nom);
	Color(j1->pion_couleur_w, 0);
	printf("%c", j1->symbole);
	Color(15,0);
	printf(")\n");
	#endif

	#ifdef linux
	printf("Joueur 1: %s(", j1->nom);

	switch(j1->pion_couleur_l)
	{
		case 31:
			couleur("31");
			break;
		case 33:
			couleur("33");
			break;
		case 34:
			couleur("34");
			break;
		case 35:
			couleur("35");
			break;
		default:
			couleur("38");
			break;
	}

	printf("%c", j1->symbole);
	couleur("0");
	printf(")\n");
	#endif

	
	strcpy(j2->nom, "IA");

	j2->symbole = caractere_IA(j1->symbole);

	if('a'<=j2->symbole && j2->symbole <= 'z')
	{
		j2->symbole = j2->symbole - ('a' - 'A');
	}

	
	printf("Joueur 2: %s(%c)\n", j2->nom, j2->symbole);

	js[0] = j1;
	js[1] = j2;

	return js;
}


int pos_aleatoire(char *tab)
{
	int i, n = 0, *indices = NULL, j = 0, iPOS, POS;
	for(i=0;i<N;i++)
		if(tab[i]=='-')
			n++;

	indices = malloc(sizeof(int)*n);
	if(!indices)
		exit(0);

	for(i=0;i<N;i++)
	{
		if(tab[i]=='-')
		{
			indices[j] = i;
			j++;
		}
	}
	srand(time(NULL));
	iPOS = rand()%n;
	POS = indices[iPOS];
	free(indices);
	return POS;
}


void j_vs_ia1(joueur **js, char *tab)
{
	char pos[2]="c";
	int POS;
	
	FILE *f = fopen("save_auto", "w+");
	int NIVEAU = 1;

	// partie statistiques
	infos *player = creer_infos(js[0]->nom);
	rechercher_joueur(player);
	
	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/

		set_nb_parties(player); // incrémenter le nombre de parties

		/* Sauvegarde automatique*/
		save_auto(f, tab, N);
		/* FIN Sauvegarde automatique*/

		affiche_table(tab,js);

		while(statut_jeu(tab, js) == -1)
		{
			
			
			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[0]->nom, js[0]->symbole);
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player))
						{
							printf("***PARTIE SAUVEGARDEE***\n");
						}
						else
						{
							printf("***PARTIE NON SAUVEGARDEE***\n");
						}

					if(pos[0]=='Q' || pos[0]=='q')
					{
						menu();
						return;
					}   

					if(pos[0]=='A' || pos[0]=='a')
					{
						affiche_table(tab, js);
						
					}
					/*FIN Sauvegarder ou quitter*/

				}while(si_nombre(pos) == 0);
				POS = pos[0];
				
			}while(si_case_occupee(tab, POS) == 1);
			
			tab[POS] = js[0]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/

			affiche_table(tab,js);
			
			if(statut_jeu(tab, js)==1)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[0]->nom,js[0]->symbole);
               
				set_nb_parties_g(player);// incréménter le nombre de parties gagnées

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");

				set_nb_parties_n(player);// incréménter le nombre de parties nulles

				break;
			}

			POS = pos_aleatoire(tab);
			
			tab[POS] = js[1]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/

			printf("%s(%c) joue:\n", js[1]->nom, js[1]->symbole);
			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nDommage !!! %s(%c) PERD !!!\n", js[0]->nom,js[0]->symbole);
                
				set_nb_parties_p(player);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				

				set_nb_parties_n(player);// // incréménter le nombre de parties nulles

				break;
			}
		}
		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player))
					printf("***PARTIE SAUVEGARDEE***\n");
				else
					printf("***PARTIE NON SAUVEGARDEE***\n");

			else if(pos[0]=='n' || pos[0]=='N')
				break;

		}while(pos[0] != 'O' && pos[0]!= 'o');	


		do
		{
			printf("\nFaire une autre partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);

		}while(si_oui_non(pos) == 0);

	}while(pos[0] == '0' || pos[0] == 'o');

	update_statistiques(player);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTOT------------\n");

}


int position_perdante(joueur **js,char *tab)

{
	int i;
	for(i=0;i<3;i++)
	{	
            
		if(tab[i]== js[0]->symbole && tab[i]==tab[i+3]  && tab[i+6]=='-')
			return i+6;
		if(tab[i]== js[0]->symbole && tab[i]==tab[i+6] && tab[i+3]=='-')
			return i+3;
		if(tab[i+3]== js[0]->symbole && tab[i+3]==tab[i+6] && tab[i]=='-')
			return i;
	}
	for(i=0;i<7;i+=3)
	{	
           
		if(tab[i]== js[0]->symbole &&  tab[i]==tab[i+1] && tab[i+2]=='-')
			return i+2;
		if(tab[i]== js[0]->symbole && tab[i]==tab[i+2] && tab[i+1]=='-')
			return i+1;
		if(tab[i+1]== js[0]->symbole && tab[i+1]==tab[i+2] && tab[i]=='-')
			return i;
	}
	if(tab[0]== js[0]->symbole && tab[0]==tab[4] && tab[8]=='-')
		return 8;
	if(tab[0]== js[0]->symbole && tab[0]==tab[8] && tab[4]=='-')
		return 4;
	if(tab[4]== js[0]->symbole && tab[4]==tab[8] && tab[0]=='-')
		return 0;
	if(tab[2]== js[0]->symbole && tab[2]==tab[4] && tab[6]=='-')
		return 6;
	if(tab[2]== js[0]->symbole && tab[2]==tab[6] && tab[4]=='-')
		return 4;
	if(tab[4]== js[0]->symbole && tab[4]==tab[6] && tab[2]=='-')
		return 2;

return -1;
}

void tour_ia2(joueur **js, char *tab)
{
	
	int i,j;
	i=position_perdante(js,tab);
	
	if(i==-1)
	{

		j = pos_aleatoire(tab);
			
		tab[j] = js[1]->symbole;
	}
	else
		tab[i] = js[1]->symbole;
}

void j_vs_ia2(joueur **js, char *tab)
{
   
   	char pos[2]="c";
	int POS;
	FILE *f = fopen("save_auto", "w+");
	int NIVEAU = 2;

	// partie statistiques
		infos *player = creer_infos(js[0]->nom);
		rechercher_joueur(player);

	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/

		set_nb_parties(player); // incrémenter le nombre de parties

		/* Sauvegarde automatique*/
		save_auto(f, tab, N);
		/* FIN Sauvegarde automatique*/
		affiche_table(tab,js);
		while(statut_jeu(tab, js) == -1)
		{
			
			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[0]->nom, js[0]->symbole);
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player))
						{
							printf("***PARTIE SAUVEGARDEE***\n");
						}
						else
						{
							printf("***PARTIE NON SAUVEGARDEE***\n");
						}


					if(pos[0]=='Q' || pos[0]=='q')
				     {
				     	menu();
				     	return;
				     }   


				    if(pos[0]=='A' || pos[0]=='a')
					{
						affiche_table(tab, js);
						
					}
					/*FIN Sauvegarder ou quitter*/

				}while(si_nombre(pos) == 0);
				POS = pos[0];
				
			}while(si_case_occupee(tab, POS) == 1);
			
			tab[POS] = js[0]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/

			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==1)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[0]->nom,js[0]->symbole);
				
                
				set_nb_parties_g(player);// incréménter le nombre de parties gagnées

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				set_nb_parties_n(player);// incréménter le nombre de parties nulles

				break;
			}

			

            tour_ia2(js,tab);
			
            /* Sauvegarde automatique*/
            save_auto(f, tab, N);
            /* FIN Sauvegarde automatique*/

            printf("%s(%c) joue:\n", js[1]->nom, js[1]->symbole);
			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nDommage !!! %s(%c) PERD !!!\n", js[0]->nom,js[0]->symbole);
               
				set_nb_parties_p(player);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				

				set_nb_parties_n(player);// // incréménter le nombre de parties nulles

				break;
			}
		}
		
		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player))
					printf("***PARTIE SAUVEGARDEE***\n");
				else
					printf("***PARTIE NON SAUVEGARDEE***\n");

			else if(pos[0]=='n' || pos[0]=='N')
				break;

		}while(pos[0] != 'O' && pos[0]!= 'o');	


		do
		{
			printf("\nFaire une autre partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);

		}while(si_oui_non(pos) == 0);

	}while(pos[0] == '0' || pos[0] == 'o');
	
	update_statistiques(player);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTOT------------\n");

}

int position_gagnante(joueur **js,char *tab)

{
	int i;
	for(i=0;i<3;i++)
	{	
            
		if(tab[i]== js[1]->symbole && tab[i]==tab[i+3]  && tab[i+6]=='-')
			return i+6;
		if(tab[i]== js[1]->symbole && tab[i]==tab[i+6] && tab[i+3]=='-')
			return i+3;
		if(tab[i+3]== js[1]->symbole && tab[i+3]==tab[i+6] && tab[i]=='-')
			return i;
	}
	for(i=0;i<7;i+=3)
	{	
           
		if(tab[i]== js[1]->symbole &&  tab[i]==tab[i+1] && tab[i+2]=='-')
			return i+2;
		if(tab[i]== js[1]->symbole && tab[i]==tab[i+2] && tab[i+1]=='-')
			return i+1;
		if(tab[i+1]== js[1]->symbole && tab[i+1]==tab[i+2] && tab[i]=='-')
			return i;
	}
	if(tab[0]== js[1]->symbole && tab[0]==tab[4] && tab[8]=='-')
		return 8;
	if(tab[0]== js[1]->symbole && tab[0]==tab[8] && tab[4]=='-')
		return 4;
	if(tab[4]== js[1]->symbole && tab[4]==tab[8] && tab[0]=='-')
		return 0;
	if(tab[2]== js[1]->symbole && tab[2]==tab[4] && tab[6]=='-')
		return 6;
	if(tab[2]== js[1]->symbole && tab[2]==tab[6] && tab[4]=='-')
		return 4;
	if(tab[4]== js[1]->symbole && tab[4]==tab[6] && tab[2]=='-')
		return 2;

return -1;
}
void tour_ia3(joueur **js, char *tab)
{
	
	int i,j;
	i=position_gagnante(js,tab);
	if(i!=-1)
		{
			tab[i] = js[1]->symbole;
			return ;
		}

	j=position_perdante(js,tab);
	if(j!=-1)
		{
			tab[j] = js[1]->symbole;
			return ;
		}
	else
	{

		j = pos_aleatoire(tab);
			
		tab[j] = js[1]->symbole;
	}
	
}
void j_vs_ia3(joueur **js, char *tab)
{
   
   	char pos[2]="c";
	int POS;
	FILE *f = fopen("save_auto", "w+");
	int NIVEAU = 3;

	// partie statistiques
		infos *player = creer_infos(js[0]->nom);
		rechercher_joueur(player);

	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/

		set_nb_parties(player); // incrémenter le nombre de parties

		/* Sauvegarde automatique*/
		save_auto(f, tab, N);
		/* FIN Sauvegarde automatique*/

		affiche_table(tab,js);
		while(statut_jeu(tab, js) == -1)
		{
		
			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[0]->nom, js[0]->symbole);
		
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player))
						{
							printf("***PARTIE SAUVEGARDEE***\n");
						}
						else
						{
							printf("***PARTIE NON SAUVEGARDEE***\n");
						}


					if(pos[0]=='Q' || pos[0]=='q')
					{
						menu();
						return;
					}   

					if(pos[0]=='A' || pos[0]=='a')
					{
						affiche_table(tab, js);
						
					}
					/*FIN Sauvegarder ou quitter*/

				}while(si_nombre(pos) == 0);
				POS = pos[0];
				
			}while(si_case_occupee(tab, POS) == 1);
			
			tab[POS] = js[0]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/
			
			affiche_table(tab,js);
			
			if(statut_jeu(tab, js)==1)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[0]->nom,js[0]->symbole);
				
               
				set_nb_parties_g(player);// incréménter le nombre de parties gagnées

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				
				set_nb_parties_n(player);// incréménter le nombre de parties nulles

				break;
			}

			

            tour_ia3(js,tab);

            /* Sauvegarde automatique*/
            save_auto(f, tab, N);
            /* FIN Sauvegarde automatique*/
			printf("%s(%c) joue:\n", js[1]->nom, js[1]->symbole);
			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nDommage !!! %s(%c) PERD !!!\n", js[0]->nom,js[0]->symbole);
                
				set_nb_parties_p(player);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				

				set_nb_parties_n(player);// // incréménter le nombre de parties nulles

				break;
			}
		}
			

		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player))
					printf("***PARTIE SAUVEGARDEE***\n");
				else
					printf("***PARTIE NON SAUVEGARDEE***\n");

			else if(pos[0]=='n' || pos[0]=='N')
				break;

		}while(pos[0] != 'O' && pos[0]!= 'o');	

		do
		{
			printf("\nFaire une autre partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			
		}while(si_oui_non(pos) == 0);

	}while(pos[0] == '0' || pos[0] == 'o');

	update_statistiques(player);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTOT------------\n");

}


void tour_ia4(char *tab,joueur **js)
{
	int deplace=-1,score=-2,tempscore,i;
	
	for(i=0;i<9;i++)
	{
	  if(tab[i]=='-')
	  {
	    tab[i]=js[1]->symbole;
	     tempscore=-min_max(tab,js,js[0]->symbole);
	    tab[i]='-';
	    if(tempscore>score)
	    {
	    	score=tempscore ;
	    	deplace=i;
	    }
	  }
	}
	tab[deplace]=js[1]->symbole;
}

void j_vs_ia4(joueur **js, char *tab)
{
   
   	char pos[2]="c";
	int POS;
	FILE *f = fopen("save_auto", "w+");
	int NIVEAU =4;

	// partie statistiques
		infos *player = creer_infos(js[0]->nom);
		rechercher_joueur(player);

	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/

		set_nb_parties(player); // incrémenter le nombre de parties

		/* Sauvegarde automatique*/
		save_auto(f, tab, N);
		/* FIN Sauvegarde automatique*/

		affiche_table(tab,js);

		while(statut_jeu(tab, js) == -1)
		{
			
			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[0]->nom, js[0]->symbole);
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player))
						{
							printf("***PARTIE SAUVEGARDEE***\n");
						}
						else
						{
							printf("***PARTIE NON SAUVEGARDEE***\n");
						}


					if(pos[0]=='Q' || pos[0]=='q')
					{
						menu();
						return;
					}   

					if(pos[0]=='A' || pos[0]=='a')
					{
						affiche_table(tab, js);
						
					}
					/*FIN Sauvegarder ou quitter*/

				}while(si_nombre(pos) == 0);
				POS = pos[0];
				
			}while(si_case_occupee(tab, POS) == 1);
			
			tab[POS] = js[0]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/

			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==1)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[0]->nom,js[0]->symbole);
                
				set_nb_parties_g(player);// incréménter le nombre de parties gagnées
				

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
               
				set_nb_parties_n(player);// incréménter le nombre de parties nulles

				break;
			}

			

            tour_ia4(tab,js);
			
            /* Sauvegarde automatique*/
            save_auto(f, tab, N);
            /* FIN Sauvegarde automatique*/

            printf("%s(%c) joue:\n", js[1]->nom, js[1]->symbole);
			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nDommage !!! %s(%c) PERD !!!\n", js[0]->nom,js[0]->symbole);
                
				set_nb_parties_p(player);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				
				set_nb_parties_n(player);// // incréménter le nombre de parties nulles

				break;
			}
		}
		
		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player))
					printf("***PARTIE SAUVEGARDEE***\n");
				else
					printf("***PARTIE NON SAUVEGARDEE***\n");

			else if(pos[0]=='n' || pos[0]=='N')
				break;

		}while(pos[0] != 'O' && pos[0]!= 'o');	


		do
		{
			printf("\nFaire une autre partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);

		}while(si_oui_non(pos) == 0);

	}while(pos[0] == '0' || pos[0] == 'o');

	update_statistiques(player);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTOT------------\n");

}



