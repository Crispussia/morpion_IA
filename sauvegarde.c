#include "morpion.h"

/*Cette fonction renvoie 1 si la partie existe déjà et 0 sinon*/
int si_partie_existe (char *nom)
{

   FILE *g = fopen("liste_noms","a+");
   //ouvrir le fichier ecriture à la fin. C'est pour éviter de 
   //supprimer les données déjà existantes
   //liste_noms est un fichier contenant la liste de toutes
   //les parties précemment sauvagardées

   fseek(g, 0, SEEK_SET); // se positionner au début du fichier
   char b = 'a';
   char t[20]; //chaine temporaire contenant le nom de chaque sauvegarde
   int i;
   while(b!=EOF)
    {
	   for(i=0;b!=EOF;i++)
	     {
	       b=fgetc(g);
	       //ce if c'est pour eviter de mettre '\n' et EOF dans la chaine t[]
		   if(b!=EOF && b!='\n')
		     {
			   t[i]=b;
			 }
		   if (b=='\n')
			break; 
	
	      }
        
         t[i]='\0';
       if(strncmp(nom,t,maxi(strlen(t), strlen(nom)))==0)
          {
       	    fclose(g);
       	    return 1;
          }
	} 

  	fclose(g);
 	return 0;	
}

/*ajoute une nouvelle sauvegarde au fichier*/
void ajout_nom (char* nom)
{
	FILE *F;
	F=fopen("liste_noms","a+");
    fprintf(F,"%s\n",nom);
    fclose(F);
}


/*Cette fonction sauvegarde la partie dans un fichier dont le nom est donné par
l'utilisateur à partir d'un fichier de sauvegarde "save_auto". Elle reçoit un pointeur g*/
int sauvegarde (FILE *g, char tab[], int n, joueur** js, int NIVEAU, infos *player)
{
	FILE *fichier = NULL, *f;
	int i, c = 1; 
	char nom[20], rep[2];
	char fin = '\n';

	do
	{

		printf("\nDonnez le nom de votre sauvegarde: ");
		read_c(nom, 20);


	


		if(si_partie_existe(nom))
		{

			
			do
			{
				printf("Cette partie existe déjà ! Voulez-vous l'ecraser ?\nO-Oui\nN-Non\n");
				read_c(rep, 2);
			}while(rep[0]!='O' && rep[0]!='o' && rep[0]!='N' && rep[0]!='n');
			//printf("\naaaaaa\n");

			if(rep[0]=='o' || rep[0] == 'O')
			{

				/* Enregistrer le nom de la partie pour les statisques */
				set_nb_parties_s(player, nom);


				f = fopen(nom, "w");
				
				if(f == NULL)
				{
					return 0;
				}
				else
				{
					fseek(g, 0, SEEK_SET);
					if(g!=NULL)
					{

						while(c!=EOF)
						{
							c = fgetc(g);
							if(c!=EOF)
								fputc(c, f);
						}
					}
					
					/*Mettre le nom des joueurs et leurs symboles à la fin du fichier sauvegarde*/

					fprintf(f, "%s-%c-%s-%c-%d", js[0]->nom, js[0]->symbole, js[1]->nom, js[1]->symbole, NIVEAU);

				}
			
				affiche_table(tab,js);
				fclose(f);
				return 1;
			}
		}
		else
		{

			/* Enregistrer le nom de la partie pour les statisques */
			set_nb_parties_s(player, nom);

			
			fichier = fopen(nom, "w");

			if(fichier==NULL)
				return 0;
			else
			{
				fseek(g, 0, SEEK_SET);
				if(g!=NULL)
				{

					while(c!=EOF)
					{
						c = fgetc(g);
						if(c!=EOF)
							fputc(c, fichier);
					}
				}

				/*Mettre le nom des joueurs et leurs symboles dans le fichier sauvegarde*/
				fprintf(fichier, "%s-%c-%s-%c-%d", js[0]->nom, js[0]->symbole, js[1]->nom, js[1]->symbole, NIVEAU);
				
			}
			ajout_nom(nom);
			fclose(fichier);
			affiche_table(tab,js);
			return 1;
		}
		
	}while(rep[0] == 'N' || rep[0] == 'n');
}


void save_auto(FILE *f, char *tab, int n)
{
	int i;
	char fin = '\n';
	if(f!=NULL)
	{

		for(i=0;i<n;i++)
			fprintf(f,"%c",tab[i]);
		fprintf(f, "%c", fin);

	}
}



int charger_partie(char tab[],int n, joueur** js, int* NIVEAU)
{
	FILE *fichier = NULL; 
	char nom[20], temp[50];
	char ch[20];
	int k = 0, j = 0;
	int i = 0;
	char c = '-';


	printf("\nEntrez le nom de la partie: ");
	read_c(nom, 20);
	
	if(si_partie_existe(nom))
	{
			fichier=fopen(nom,"r");
			if(fichier==NULL)
			   	return 0;

			do
			{
				i = 0;
			
				do
				{
					
					c = fgetc(fichier);
					
					if(c!=EOF && c!='\n')
					{
						temp[i] = c;
						
						i++;
					}
				}while(c!='\n' && c!=EOF);

				temp[i] = '\0';
				
			}while(c!=EOF);

			

		

			/*On se positionne ici au début de l'avant dernière ligne
			  du fichier*/
			fseek(fichier, -strlen(temp)-10, SEEK_CUR);
			
			//printf("Cur: %c\n", c);
			/*insertion de l'avant dernière ligne dans tab
			  C'est en effet le dernier état de la partie
			*/
			for(i=0;i<n;i++)
			{
				c = fgetc(fichier);
				tab[i] = c;
			}

			i = 0; //ramener i à 0

			/*
				on extait ici les noms, les symboles et le niveau de la 
				partie. Toutes ces informations se trouvent sur la dernière 
				ligne du fichier
			*/
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
					case 5:
						*NIVEAU = atoi(ch);
						break;
				}

			}while(i<strlen(temp));

			fclose(fichier);
			
			return 1;
	}
	else
	{
		printf("Cette partie n'existe pas !\n");
		return 0;
	}

}
