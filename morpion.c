#include "morpion.h"

 
void init_table(char *table)
{
	int i;
	for(i=0;i<N;i++)
	{
		table[i] = '-';
	}
}


#ifdef linux
void affichecouleur(char c, joueur **js)
{ 


	if(c==js[0]->symbole)
	{

		switch(js[0]->pion_couleur_l)
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

		printf("%c",c);
	    couleur("0");
	}
	if(c==js[1]->symbole)
	{
		switch(js[1]->pion_couleur_l)
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
	    printf("%c",c);
	    couleur("0");
     }

    if(c=='-')
	{
		couleur("37");
	   	printf("-");
	    couleur("0");
    }

}
void affiche_table(char *table, joueur **js)
{
	int i, j;
	printf("\n");
  
	for(i=0;i<=N;i++)
	{  
		if(i%(int)sqrt(N)==0 && i!=0)
		{           
	    	printf("\t|****|****|****|\n");
            printf("\t| ");
            affichecouleur(table[i-3],js);
            printf("  | ");
            affichecouleur(table[i-2],js);
            printf("  | ");
            affichecouleur(table[i-1],js);
            printf("  |    ");
                  
			if(i!=0 || i == N-1)
				for(j=3;j>0;j--)
				{
					printf("%d", i-j+1);
					printf("    ");
				}

				printf("\n");
				printf("\t|    |    |    |\n");
		}



	}
printf("\t****************\n");
}
#endif


#ifdef _WIN32
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void affichecouleur(char c, joueur**js)
{


	
	if(c==js[0]->symbole)
	{
		Color(js[0]->pion_couleur_w, 0);
	    printf("%c",c);
   		Color(15, 0);
	}
	if(c==js[1]->symbole)
	{
		Color(js[1]->pion_couleur_w, 0);
	    printf("%c",c);
	    Color(15,0);
     }

     if(c=='-')
	{
		Color(15,0);
	    printf("-");
	    Color(15,0);
    }
    
	
}

void affiche_table(char *table,joueur **js)
{
	int i, j;
	printf("\n");
  
	for(i=0;i<=N;i++)
	{  
		if(i%(int)sqrt(N)==0 && i!=0)
		{           
	        printf("\t|****|****|****|\n");
            printf("\t| ");
            affichecouleur(table[i-3],js);
            printf("  | ");
            affichecouleur(table[i-2],js);
            printf("  | ");
            affichecouleur(table[i-1],js);
            printf("  |    ");
                  
			if(i!=0 || i == N-1)
				for(j=3;j>0;j--)
				    {
						printf("%d", i-j+1);
						printf("    ");
				    }

				printf("\n");
				printf("\t|    |    |    |\n");
		}



	}
printf("\t****************\n");

}

#endif 
 


joueur *creer_joueur()
{
	joueur *j = malloc(sizeof(joueur));

	if(j == NULL)
		exit(0);

	j->pion_couleur_l = 5;
	j->pion_couleur_w = 15;
 	return j;
}


joueur** init_joueurs_perso()
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
	

	printf("Joueur 2\n");
	printf("Entrez votre nom : ");

	read_c(j2->nom, 20);

	do
	{
		printf("Choisissez votre symbole : (caratere alphabetique) ");
		read_c(sym, 2);
	}while(si_alpha(sym) == 0 || sym[0] == j1->symbole || sym[0] == j1->symbole+('a'-'A') );

	if('a'<=sym[0] && sym[0] <= 'z')
	{
		j2->symbole = sym[0] - ('a' - 'A');
	}
	else
	{
		j2->symbole = sym[0];
	}
	
	choix_couleur_joueur(j2);

	#ifdef _WIN32
	printf("Joueur 2: %s(", j2->nom);
	Color(j2->pion_couleur_w, 0);
	printf("%c", j2->symbole);
	Color(15,0);
	printf(")\n");
	#endif

	#ifdef linux
	printf("Joueur 2: %s(", j2->nom);

	switch(j2->pion_couleur_l)
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

	printf("%c", j2->symbole);
	couleur("0");
	printf(")\n");
	#endif

	js[0] = j1;
	js[1] = j2;


	return js;
}

int statut_jeu(char *tab, joueur **js)
{
	
	int i;
    if((tab[0] == tab[1] && tab[1] == tab[2] && tab[0] == js[0]->symbole )||
	   (tab[3] == tab[4] && tab[4] == tab[5] && tab[3] == js[0]->symbole )||
	   (tab[6] == tab[7] && tab[7] == tab[8] && tab[6] == js[0]->symbole )||
	   (tab[0] == tab[3] && tab[3] == tab[6] && tab[0] == js[0]->symbole )||
	   (tab[1] == tab[4] && tab[4] == tab[7] && tab[1] == js[0]->symbole )||
	   (tab[2] == tab[5] && tab[5] == tab[8] && tab[2] == js[0]->symbole )||
	   (tab[0] == tab[4] && tab[4] == tab[8] && tab[0] == js[0]->symbole )||
	   (tab[2] == tab[4] && tab[4] == tab[6] && tab[2] == js[0]->symbole ))
	   return 1; // pour signifier que le joueur 1 a gagné
	
		
	else if((tab[0] == tab[1] && tab[1] == tab[2] && tab[0] == js[1]->symbole )||
		    (tab[3] == tab[4] && tab[4] == tab[5] && tab[3] == js[1]->symbole )||
		    (tab[6] == tab[7] && tab[7] == tab[8] && tab[6] == js[1]->symbole )||
		    (tab[0] == tab[3] && tab[3] == tab[6] && tab[0] == js[1]->symbole )||
		    (tab[1] == tab[4] && tab[4] == tab[7] && tab[1] == js[1]->symbole )||
		    (tab[2] == tab[5] && tab[5] == tab[8] && tab[2] == js[1]->symbole )||
		    (tab[0] == tab[4] && tab[4] == tab[8] && tab[0] == js[1]->symbole )||
		    (tab[2] == tab[4] && tab[4] == tab[6] && tab[2] == js[1]->symbole ))
		return 2; // pour signifier que le joueur 2 a gagné

	for(i=0;i<N;i++)
	{
		if(tab[i] == '-')
			return -1; // -1 signifie que le jeu est toujours en cours
	}

	if(i==N)
		return 0; // signifie que le match est nul
}

int si_case_occupee(char *tab, int pos) //fonction qui retourne 1 si la case est occupee et 0 sinon
{
	if(tab[pos] == '-')
		return 0;
	else
		return 1;
}

void debut_jeu(joueur **js, char *tab)
{
	char pos[2]="c";
	int POS;
	FILE *f = fopen("save_auto", "a+");
	int NIVEAU = 0;

	// partie statistiques
			infos *player0 = creer_infos(js[0]->nom);
			rechercher_joueur(player0);

			infos *player1 = creer_infos(js[1]->nom);
			rechercher_joueur(player1);

	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/

		set_nb_parties(player0); // incrémenter le nombre de parties
		set_nb_parties(player1); // incrémenter le nombre de parties

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
						if(sauvegarde(f, tab, N, js, NIVEAU, player0))
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
				
				

				set_nb_parties_g(player0);// incréménter le nombre de parties gagnées
				set_nb_parties_p(player1);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
                
				set_nb_parties_n(player0);// incréménter le nombre de parties nulles
				set_nb_parties_n(player1);// incréménter le nombre de parties nulles

				break;
			}


			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[1]->nom, js[1]->symbole);
					
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player1))
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
			
			tab[POS] = js[1]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/


			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[1]->nom,js[1]->symbole);
                
				set_nb_parties_p(player0);// incrémenter le nombre de parties perdues
				set_nb_parties_g(player1);// incréménter le nombre de parties gagnées

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
                
				set_nb_parties_n(player0);// // incréménter le nombre de parties nulles
				set_nb_parties_n(player1);// // incréménter le nombre de parties nulles


				break;
			}
		}
			

		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player0))
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

	update_statistiques(player0);
	update_statistiques(player1);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTÔT------------\n");

}



void debut_jeu1(joueur **js, char *tab)
{
	char pos[2]="c";
	int POS;
	FILE *f = fopen("save_auto", "a+");
	int NIVEAU = 0;

	// partie statistiques
		infos *player0 = creer_infos(js[0]->nom);
		rechercher_joueur(player0);

		infos *player1 = creer_infos(js[1]->nom);
		rechercher_joueur(player1);

	do
	{
		if(pos[0]!='c')
			init_table(tab);/*ce if empeche l'initialisation de la table lors du chargement*/


		set_nb_parties(player0); // incrémenter le nombre de parties
		set_nb_parties(player1); // incrémenter le nombre de parties

		/* Sauvegarde automatique*/
		save_auto(f, tab, N);
		/* FIN Sauvegarde automatique*/



		while(statut_jeu(tab, js) == -1)
		{
			affiche_table(tab,js);
			
			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[1]->nom, js[1]->symbole);
					
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player1))
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
			
			tab[POS] = js[1]->symbole;

			/* Sauvegarde automatique*/
			save_auto(f, tab, N);
			/* FIN Sauvegarde automatique*/


			affiche_table(tab,js);
			

			if(statut_jeu(tab, js)==2)
			{
				printf("\nFelicitations !!! %s(%c) GAGNE !!!\n", js[1]->nom,js[1]->symbole);
                
				set_nb_parties_g(player1);// incréménter le nombre de parties gagnées
				set_nb_parties_p(player0);// incrémenter le nombre de parties perdues

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
                 
				set_nb_parties_n(player0);// // incréménter le nombre de parties nulles
				set_nb_parties_n(player1);// // incréménter le nombre de parties nulles

				break;
			}

			do
			{
				do
				{
					printf("\n%s(%c) a vous de jouer (A-Afficher Jeu S-Sauvegarger Q-Quitter):  ", js[0]->nom, js[0]->symbole);
					
					read_c(pos, 2);

					/*Sauvegarder ou quitter*/

					if(pos[0]=='S' || pos[0]=='s')
						if(sauvegarde(f, tab, N, js, NIVEAU, player0))
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
               
				set_nb_parties_p(player1);// incrémenter le nombre de parties perdues
				set_nb_parties_g(player0);// incréménter le nombre de parties gagnées

				break;
			}
			else if(statut_jeu(tab, js) == 0)
			{
				printf("\n--------MATCH NUL !!!--------\n");
				
				set_nb_parties_n(player0);// // incréménter le nombre de parties nulles
				set_nb_parties_n(player1);// // incréménter le nombre de parties nulles

				break;
			}


		}
			

		/*Demander sauvegarde de la partie*/
		do
		{
			printf("Sauvegarder la partie ?\nO-Oui\nN-Non\n");
			read_c(pos, 2);
			if(pos[0]=='o' || pos[0]=='O')
				if(sauvegarde(f, tab, N, js, NIVEAU, player0))
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

	update_statistiques(player0);
	update_statistiques(player1);

	fclose(f);
	printf("\n--------FIN DE LA PARTIE--------\n");
	printf("\n-----------A BIENTÔT------------\n");

}

void lancer_partie(char*tab,joueur **js, int NIVEAU)
{
  int i,n=0;
  int k = statut_jeu(tab, js);
  char ch[2];

  #ifdef _WIN32
  js[0]->pion_couleur_w = 15;
  js[1]->pion_couleur_w = 15;
  #endif

  if( k != -1 )
  {
  	printf("Cette partie est terminee !!!\n");
  	switch(k)
  	{
  		case 0:
  			printf("\nC'etait un match nul entre %s(%c) et %s(%c).\n", js[0]->nom, js[0]->symbole, js[1]->nom, js[1]->symbole);
  			break;
  		case 1:
  			printf("\n%s(%c) avait remporte le match contre %s(%c).\n", js[0]->nom, js[0]->symbole, js[1]->nom, js[1]->symbole);
  			break;
  		case 2:
  			printf("\n%s(%c) avait remporte le match contre %s(%c).\n", js[1]->nom, js[1]->symbole, js[0]->nom, js[0]->symbole);
  			break;
  	}
  	printf("\nAppuyez sur entrée pour continuer...\n");
  	read_c(ch, 2);
  }
  else
  {
  	switch(NIVEAU)
  	{
  		case 0:
  			for(i=0;i<N;i++)
  			{
  				if(tab[i]=='O'||tab[i]=='X')
  					n++;
  			}
  			if(n%2==0)
  				debut_jeu(js,tab);
  			else
  				debut_jeu1(js,tab);

  			break;
  		case 1:
  			j_vs_ia1(js,tab);
  		    break;
  		case 2:
  			j_vs_ia2(js,tab);
  		    break;
  		case 3:
  			j_vs_ia3(js,tab);
  		    break;
  		case 4:
  			j_vs_ia4(js,tab);
  		    break;
  	}
  }
  
}



void visualiser_partie()
{
	char nom[20];
	char choix[2];
	FILE *f = NULL;
	char c;
	int i, j = 0, k = 0;
	char temp[50];
	int n = 0;
	char chaine[500];
	char ch[20];
	joueur **js = malloc(sizeof(joueur*)*2);
	js[0] = malloc(sizeof(joueur));
	js[1] = malloc(sizeof(joueur));
	char entree[2];

	#ifdef _WIN32
	js[0]->pion_couleur_w = 15;
	js[1]->pion_couleur_w = 15;
	#endif

		printf("Entrez la partie que vous voulez visualiser: ");
		read_c(nom, 20);

		if(si_partie_existe(nom))
		{
			f = fopen(nom, "r");
			n = 0; /* ramener n à 0. Important lorsqu'on veut visualiser une 
					autre partie. */
			/*
			cette boucle nous permet de compter le nombre de carctères
			se trouvant dans notre fichier
			*/
			do
			{
				c = fgetc(f);	
				n++;
			}while(c!=EOF);

			/*
			On se repositionne ensuite au début du fichier
			*/
			fseek(f, 0, SEEK_SET);

			//cette boucle parcourt chaque caractère du fichier
			do
			{
				i = 0;
				
				/*
				Avec cette boucle, on récupère chaque ligne du fichier 
				dans le tableau temp mais c'est la dernière ligne qui 
				nous intéresse
				*/
				do
				{
					
					c = fgetc(f);
					if(c!=EOF && c!='\n')
					{
							temp[i] = c;
							i++;
					}

				}while(c!='\n' && c!=EOF);

			}while(c!=EOF);/* à la fin de cette ligne temp contient la dernière 
							  du fichier. De cette ligne sera extraite les noms des 
							  joueurs et leur symbole			
						   */
			temp[i] = '\0';
			n = n - strlen(temp)-1; /*Ici on met dans n le nombre de caratères se 
								   	  se trouvant avant la dernière ligne 
								 	*/
			
			fseek(f, 0, SEEK_SET); /*On se positionne au début du fichier*/

			/* On met dans chaine tous les caractères se trouvant avant la dernière
			   ligne de notre fichier
			*/
			for (i = 0; i < n; i++)
			{
				c = fgetc(f);
				chaine[i] = c;
			}
			chaine[i] = '\0';
			

			/*Extraire les noms et symboles des joueurs*/
			//printf("temp: %s\nchaine:%s\n", temp, chaine);
			i = 0; // ramener i à 0
			do
			{
				while(i<strlen(temp))
				{	
					if(temp[i]!='-')
					{
						ch[j]=temp[i];
						i++;
						j++;
					}
					else
					{
						i++;
						break;
					}
			
				}

				ch[j] = '\0';
				j = 0;
				k++;

				switch(k)//k compte le nombre de tirets dans la dernière ligne du fichier
				{
					case 1:
						//printf("1: %s\n", ch);
						strcpy(js[0]->nom, ch);
						break;
					case 2:
						js[0]->symbole = ch[0];
						break;
					case 3:
						strcpy(js[1]->nom, ch);
						break;
					case 4:
						js[1]->symbole = ch[0];
						break;
				}

			}while(i<strlen(temp));/* à la fin de cette boucle on a récupérer toutes les informations
									  sur les joueurs de la partie  

									*/ 
			
			/*Extraire chaque état de la table du tableau chaine 
			  et lancer la visualisation de la partie
			*/
			
			printf("Visualisation de la partie %s...\n", nom);
			i = 0; // ramener i à 0
			k = 0; // ramener k à 0
			do
			{
				while(i<strlen(chaine))
				{	
					if(chaine[i]!='\n')
					{
						ch[j]=chaine[i];
						i++;
						j++;
					}
					else
					{
						i++;
						break;
					}
			
				}

				ch[j] = '\0';
				j = 0;
				k =  nombre_cases_occupees(ch);
				if(k) 
				{
					/*Ici on détermine quel joueur doit jouer*/
					if(k%2 == 1) // Si k%2 impair, c'est J1 qui a joué
					{
						printf("%s(%c) a joue:\n",js[0]->nom, js[0]->symbole);
						affiche_table(ch,js);
						printf("Appuez sur entree pour continuer...\n");
						read_c(entree, 2);
					}
					else //sinon c'est J2 qui a joué
					{
						printf("%s(%c) a joue: \n",js[1]->nom, js[1]->symbole);
						affiche_table(ch,js);
						printf("Appuez sur entree pour continuer...\n");
						read_c(entree, 2);
					}
				}
				else
				{
					printf("\nDEBUT DE LA PARTIE !!!\n");
					affiche_table(ch,js);
					printf("Appuez sur entree pour continuer...\n");
					read_c(entree, 2);
				}

			}while(i<strlen(chaine));


			printf("FIN DE LA PARTIE !!!\n");
		}
		else
		{
			printf("Cette partie n'existe pas !!!\n");
			return;
		}
	
	fclose(f);
}
