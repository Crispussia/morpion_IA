#include "morpion.h"


/*Cette fonction crée un élément de type infos*/
infos* creer_infos(char *nom)
{
	infos *p = malloc(sizeof(infos));
	if(!p)
		exit(0);
	else
	{
		strcpy(p->nom, nom);
		p->nb_parties = 0;
		p->nb_parties_g = 0;
		p->nb_parties_p = 0; 
		p->nb_parties_a = 0; 
		p->nb_parties_n = 0;
		strcpy(p->parties_s, "PNS"); // PN: Partie Non Sauvegardée
	}

	return p;
}

/*les fonctions de mise à jour des différents champs
	et aussi de mise à jour du fichier statistiques*/

void set_nb_parties(infos *player)
{
	player->nb_parties++; 
}

void set_nb_parties_g(infos *player)
{
	player->nb_parties_g++;
}

void set_nb_parties_p(infos *player)
{
	player->nb_parties_p++;
}

void set_nb_parties_a(infos *player)
{
	player->nb_parties_a++;
}

void set_nb_parties_n(infos *player)
{
	player->nb_parties_n++;
}


void afficher_statistiques()
{

	char cur='*';
	char ch[20], ligne[100];
	int i = 0, j = 0;
	int k = 0;//
	int compteur=1;
	FILE* f = fopen("statistiques", "a+");
	if(!f)
		exit(0);

	infos *player = malloc(sizeof(infos));


    printf("Legende:Partie Non Sauvegardee(PNS)\n");
    printf("\n************************************************\n");
    printf("|Numero");
    printf("\t|Informations");
    printf("\t\t|Valeurs\t\n");
    printf("************************************************\n");
	do
	{
		i = 0;
		
		//boucle pour récupérer chaque ligne du fichier
		do
		{
			

			cur = fgetc(f);
			if(cur!=EOF && cur!='\n')
			{
				ligne[i] = cur;
				i++;
			}
		}while(cur!=EOF && cur!='\n');

		ligne[i] = '\0'; // on spécifie la fin de ligne	

		if(ligne[0] == '#' || ligne[0] == '\n')
			continue;


				k = 0;
				i = 0;
		   		do//boucle qui parcours toute la ligne
				{

					
					k++; //compte le nombre de '|' traversés
					j = 0; //ramener j à 0. Servira de variable de parcours pour extraire 
						  //chaque colonne
				  // passer au caractère se trouvant après '|'
					do//parcours la ligne et s'arrête au caractère '|'
					{	
						

						if(ligne[i]!=EOF && ligne[i]!='|' && ligne[i]!='\0')
						{
							ch[j] = ligne[i]; //mettre dans ch les valeurs de chaque colonne
							j++;
						}
						
						i++;
					}while(ligne[i]!='|' && ligne[i]!='\0');

					
					ch[j] = '\0'; //fermer la chaine ch
		             
					
					switch(k) //on distingue les différents cas
					{
						/* On aura besoin de la fonction int atoi(const char*) de
							la bibliothèque stdlib.h
							qui convertit une chaîne de caractères en entiers*/

						case 1:
							strcpy(player->nom, ch);
							
							break;
						case 2: //  cas où l'on a extrait nb_parties
							player->nb_parties = atoi(ch);
							
							break;
						case 3: //  cas où l'on a extrait nb_parties_g
							player->nb_parties_g = atoi(ch);
							
							break;
						case 4: //  cas où l'on a extrait nb_parties_p
							player->nb_parties_p = atoi(ch);
							
							break;
						case 5: //  cas où l'on a extrait nb_parties_a
							player->nb_parties_a = atoi(ch);
							
							break;
						case 6: //  cas où on a extrait nb_parties_n
							player->nb_parties_n = atoi(ch);
							
							break;
						case 7: //  cas où on a extrait les parties sauvegardées
							strcpy(player->parties_s, ch);
							
							break;
					}
					

				}while(ligne[i]!='\0'); // a la fin de cette boucle notre structure est à jour
				if(ligne[0]!='\0')
				{
					
                    printf("|%d",compteur);
                    printf("\t|Nom: ");
                    printf("\t\t\t|%s\t\t\n", player->nom);
                    printf("| ");
                    printf("\t|Nb_parties: ");
					printf("\t\t|%d\t\t\n",player->nb_parties);
					printf("| ");
                    printf("\t|Nb_parties_gagnees: ");
					printf("\t|%d\t\t\n",player->nb_parties_g);
					printf("| ");
                    printf("\t|Nb_parties_perdues: ");
					printf("\t|%d\t\t\n",player->nb_parties_p);
					printf("| ");
                    printf("\t|Nb_parties_annulees:  ");
					printf("\t|%d\t\t\n",player->nb_parties_a);
			        printf("| ");
                    printf("\t|Nb_parties_nulles:  ");
					printf("\t|%d\t\t\n",player->nb_parties_n);
					printf("| ");
                    printf("\t|Parties sauvegardees:  ");
					printf("|%s\t\t\n",player->parties_s);
                    printf("************************************************\n");
                  
                    compteur ++;
				}
				


	}while(cur!=EOF);


	fclose(f);
	free(player);	

}


/*Cette fonction actualise le nom de toutes les sauvegardes 
du joueur */
void set_nb_parties_s(infos *player, char *nom_backup) 
{
	if(strcmp(nom_backup, "PNS") == 0) /*PNS: Partie Non Sauvegardée*/
	{
		strcpy(player->parties_s, nom_backup);
	}
	else
	{
		strcat(player->parties_s, ", "); //concaténer d'abord une virgule
		strcat(player->parties_s, nom_backup); //concaténer le nom de la nouvelle sauvegarde	
	}
	

}


void update_statistiques(infos *p)
{
	FILE* f = fopen("statistiques", "a+");
	if(!f)
		exit(0);
	else
		fprintf(f, "%s|%d|%d|%d|%d|%d|%s\n", p->nom, p->nb_parties, p->nb_parties_g, p->nb_parties_p, 
											p->nb_parties_a, p->nb_parties_n, p->parties_s);
	
	fclose(f);
}

/*Cette fonction renvoie 1 et récupère ses stats si il existe et
0 sinon sans récupérer les stats*/
int rechercher_joueur(infos *player) 
{

	FILE *f = fopen("statistiques", "r+");
	char diese[25]="#anonyme|0|0|0|0|0|PNS";
	if(!f) // si l'ouverture echoue, créer le fichier
	{
		f = fopen("statistiques", "w+");
		fprintf(f, "%s\n", diese);
		fseek(f, 0, SEEK_SET);
	}

	char cur='*';
	char ch[20], ligne[100];
	int i = 0, j = 0;
	int k = 0;// k compte le nombre de '|' rencontré
	

	/*rechercher le nom du joueur dans le fichier statistiques*/

	//important de faire des boucles do...while
	//pour ne pas sauter de caractères lors de la lecture
	do
	{
		
		//boucle pour récupérer le nom du joueur
		do
		{
			

			cur = fgetc(f);
			if(cur!=EOF && cur!='\n')
			{
				ligne[i] = cur;
				i++;
			}
		}while(cur!=EOF && cur!='\n');

		ligne[i] = '\0'; // on spécifie la fin de ligne		

		
		while(ligne[j]!='|')
		{
			ch[j]=ligne[j];
			j++;
		}

		ch[j] = '\0';

		if(strcmp(ch, player->nom) == 0)
			break;
		else
		{
			i = 0;
			j = 0;

			
		}

	}while(cur!=EOF);


	if(strlen(ch) == 0)
	{
	
		fclose(f);
		return 0; // 0 pour dire que le joueur n'est pas dans le fichier statistiques
	}
	else
	{
		fseek(f, -strlen(ligne)-1, SEEK_CUR); //ces deux lignes permettent de remplacer 
		fputc('#', f); 						  //le premier caractère du nom par '#'. En effet 
											  //on positionne d'abord sur ce caractère 
											  //avec fseek et SEEK_CUR et on le remplace
											  //A la prochaine lecture cette ligne sera juste ignorée
		fseek(f, 0, SEEK_END);	//IMPORTANT renvenir à la fin du fichier

		/*extraire toutes nos statistiques de ligne quand le joueur 
		est présent dans le fichier*/

		for(i=0;ligne[i]!='|';i++); //parcourir ligne jusqu'à tomber 
									//sur le premier '|'. La boucle for est lue comme 
									//une instruction à cause ';' à la fin
		
		
		do//boucle qui parcours toute la ligne
		{

			
			k++; //compte le nombre de '|' traversés
			j = 0; //ramener j à 0. Servira de variable de parcours pour extraire 
				  //chaque colonne
			i++;  // passer au caractère se trouvant après '|'
			do//parcours la ligne et s'arrête au caractère '|'
			{	
				

				if(ligne[i]!=EOF && ligne[i]!='|' && ligne[i]!='\0')
					ch[j] = ligne[i]; //mettre dans ch les valeurs de chaque colonne
				j++;
				i++;
			}while(ligne[i]!='|' && ligne[i]!='\0');

			
			ch[j] = '\0'; //fermer la chaine ch


			switch(k) //on distingue les différents cas
			{
				/* On aura besoin de la fonction int atoi(const char*) de
					la bibliothèque stdlib.h
					qui convertit une chaîne de caractères en entiers*/
				case 1: //  cas où l'on a extrait nb_parties
					player->nb_parties = atoi(ch);
					break;
				case 2: //  cas où l'on a extrait nb_parties_g
					player->nb_parties_g = atoi(ch);
					break;
				case 3: //  cas où l'on a extrait nb_parties_p
					player->nb_parties_p = atoi(ch);
					break;
				case 4: //  cas où l'on a extrait nb_parties_a
					player->nb_parties_a = atoi(ch);
					break;
				case 5: //  cas où on a extrait nb_parties_n
					player->nb_parties_n = atoi(ch);
					break;
				case 6: //  cas où on a extrait les parties sauvegardées
					strcpy(player->parties_s, ch);
					break;
			}

		}while(ligne[i]!='\0'); // a la fin de cette boucle notre structure est à jour

		fclose(f);
		return 1; // joueur a été trouvé et ses stats ont été insérées avec succès
	}
	
}