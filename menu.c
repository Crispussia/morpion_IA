#include "morpion.h"

void aide()
{
	printf("\n\n\t\t\t\t    AIDE \n\n\n");
	printf("\t Le jeu de \"Tic-Tac-Toe\" plus communement appele \"Morpion\" se joue a deux:\n");
	printf("\t -Vous contre un joueur humain.  \n");
	printf("\t -Vous contre l'ordinateur.  \n");
	
	printf("\t Le but du jeu est d'aligner trois meme pions. \n");
	printf("\t Les joueurs inscrivent tour a tour leur symbole sur une grille.\n");
	printf("\t Le premier qui parvient a aligner trois de ses symboles\n");
	printf("\t horizontalement, verticalement ou diagonalement  gagne la partie.\n");
	printf("\t Plusieurs niveaux de difficultes sont rencontres \n");
	printf("\t lorsque vous jouez contre l'ordinateur.\n");
	printf("\t Durant le jeu, il est possible de sauvegarder une partie,\n");
	printf("\t de revenir au menu pour restaurer une partie anterieure\n");
	printf("\t et afficher les statistiques de tous les joueurs.\n\n");
	printf("\t\t\t\t  BON JEU !!!\n\n ");
}

void menu1()
{   printf("\n###################  MENU ORDINATEUR #####################\n");
	printf("Choisissez le niveau de difficulte:\n");
	printf(" 1- Niveau facile\n");
	printf(" 2- Niveau moyen\n");
	printf(" 3- Niveau difficile\n");
	printf(" 4- Niveau Extreme\n");
	printf(" 5- Quittez \n");
    printf("###################  FIN MENU ORDINATEUR  #####################\n");

}
void menu2()
{
	
    printf("\n###################  MENU NOUVELLE PARTIE #####################\n");
    printf(" 1-Humain vs Humain \n");
    printf(" 2-Ordinateur vs Humain\n");
    printf(" 3-Quittez\n");
    printf("\n################### FIN NOUVELLE PARTIE #####################\n");
	
}

void menu3()
{   printf("###############  MENU JEU MORPION  ################\n");
	
	printf(" 1-Nouvelle Partie \n");
	printf(" 2-Charger une partie\n");
	printf(" 3-Revisualiser une partie\n");
	printf(" 4-Statistiques des joueurs\n");
	printf(" 5-Aide\n");
	printf(" 6-Quittez le jeu\n");
	printf("################ FIN MENU JEU MORPION ##################\n");


}


void menujoueurIA()
{
	
	char choix [2];
	char *table = NULL;
	joueur **js = NULL;
	
	do
	{
    menu1();
	printf("\nEntrez votre choix : ");
	read_c(choix ,2 );
		switch (choix [0])
		{
		    case '1':  
			    printf("\n******************* NIVEAU  FACILE*******************\n");
			    table = malloc(sizeof(char)*N);
			    if(!table)
			        exit(0);

			    init_table(table);
			    js = init_joueur_ia_perso();
			    j_vs_ia1(js, table);

			    free(table);
		    break;

		    case '2': 
		    	printf("\n******************* NIVEAU MOYEN*******************\n");
		     	table = malloc(sizeof(char)*N);
	            if(!table)
	                exit(0);

	                        
	            init_table(table);
	            js = init_joueur_ia_perso();
	                         
	            j_vs_ia2(js, table);

	            free(table);
		    break;

		    case '3': 

		    	printf("\n******************* NIVEAU DIFFICILE*******************\n");
		               
	            table = malloc(sizeof(char)*N);
	            if(!table)
	                exit(0);
	            init_table(table);
	            js = init_joueur_ia_perso();
	                         
	            j_vs_ia3(js, table);

	            free(table);
		    break;

		    case '4': 

		    	printf("\n******************* NIVEAU EXTREME*******************\n");
		        table = malloc(sizeof(char)*N);
		        if(!table)
		            exit(0);

		                
		        init_table(table);
		                	
		        js = init_joueur_ia_perso();
		        j_vs_ia4(js, table);

		        free(table);
		    break;
		                                       
		    case '5': 
		    	printf("\n*******************FIN DU NIVEAU*******************\n");

		    break;
		                                       
		}

	}while(choix[0]!='5');
}


void menu_newpartie()
{
	char choix2[2];
	char *table = NULL;
	
	joueur **js = NULL;
	do
	{
	menu2();
	printf("\n Entrez votre choix : ");
	read_c(choix2 , 2);
		switch (choix2[0])
		{
	        case '1': 
	          	printf("\n*******************HUMAIN vs HUMAIN*******************\n ");
	            table = malloc(sizeof(char)*N);
	            if(!table)
	                exit(0);

	            init_table(table);
	            js = init_joueurs_perso();
	            debut_jeu(js, table);

	            free(table);
                 
	        break;

	        case '2':
	        	printf("\n*******************ORDINATEUR vs HUMAIN*******************\n");
	            menujoueurIA();
	        break;
	          
	          
	        case '3': 
	          	printf("\n\t QUITTER\n ");
	        break;
	    }
    }while(choix2[0]!='3');
}

void menu()
{
	printf("*****************   BIENVENUE DANS LE JEU DE MORPION  *****************\n\n");
	
	char choixf [2];
	char *table = NULL;
	int i,NIVEAU;
	joueur **js = NULL;
	
	do
	{
	menu3();
	printf("\n Entrez votre choix : ");
	read_c(choixf , 2);
			switch (choixf[0])
			{
                 
               
                case '1':
                    menu_newpartie();
                break;

                case '2': 
                	printf("\n################ CHARGER UNE PARTIE ################ \n   ");
                                  
                    table = malloc(sizeof(char)*N);
                                  
                    if(!table)
                        exit(0);

                    js = malloc(sizeof(joueur*)*2);

                    for (i=0;i<2;i++)
                    {
                        js[i]=malloc(sizeof(joueur));
                    }

                    if(charger_partie(table,9,js,&NIVEAU))
                    {
                        printf("Chargement reussi!!!\n");
                        lancer_partie(table,js,NIVEAU);
                    }

                    else
                       	printf("Chargement non reussi!!\n");

                    free(table);
                break;
                
                case '3': 
                	printf("\n################  REVISUALISER UNE PARTIE ################  \n");
                    visualiser_partie();
                break;

                case '4': 
                	printf("\n################ STATISTIQUES DU JOUEUR ################  \n");
                                
                    afficher_statistiques();
                break;

                case '5':   
                    aide();
                break;

                case '6':
                    printf("\n################ A bientot ################ \n");
                break;
			}
    
    }while(choixf[0]!='6');

printf("***************** FIN DU JEU DE MORPION *****************\n");
}
