#include "morpion.h"

int maxi(int a, int b)
{
	return (a>=b?a:b);
}


/*recupère une chaine ne contenant qu'un seul 
caractère et renvoie le code ascii de ce caract
*/
int convert_to_int(char *s)
{
	if(!s)
		exit(0);

	return s[0];
}

/* cette fonction renvoie 1 si la chaine contient
uniquement X, x, O ou o et  0 sinon */
int si_X_O(char *s)
{
	if(strlen(s) > 1)
		return 0;
	else
	{
		if(s[0] == 'O' ||
		   s[0] == 'X' )
			return 1;
		else if(s[0] == 'o' ||
		   		s[0] == 'x' )
		{
			s[0] -= 'a'-'A'; 
			return 1;
		}
		else
			return 0;
	}
}

int si_alpha(char *s)
{
	if(strlen(s) > 1)
		return 0;
	else
	{
		if(('A'<= s[0] && s[0]<='Z') ||
			('a'<= s[0] && s[0]<='z') )
			return 1;
		else
			return 0;
	}
}

char caractere_IA (char c_joueur)
{
	char c_ia;
	do
	{
		srand(time(NULL));
		c_ia = rand()%('z' - 'A') + 'A';
	}while(c_ia == c_joueur || c_ia == c_joueur +('a'-'A') || (c_ia > 'Z' && c_ia < 'a'));

	return c_ia;
}


/* cette fonction renvoie 1 si la chaine est le 
code ascii d'un nombre entre 1 et 9 et 0 sinon */
int si_nombre(char *s)
{
	if(strlen(s) > 1)
		return 0;
	else
	{
		if('1' <= s[0] && s[0] <= '9')
		{
			s[0] -= '0'; //transformation caractère
			s[0]--;
			return 1;
		}
		else 
			return 0;
	}
}

int si_oui_non(char *s)
{
	if(strlen(s) > 1)
		return 0;
	else
	{
		if(s[0] == 'o' ||
		   s[0] == 'O' ||
		   s[0] == 'n' ||
		   s[0] == 'N' )
			return 1;
		else 
			return 0;
	}
}

void vider_buffer()
{
	char c;
	while(c!='\n')
		c = getchar();
}

void read_c(char *ch, int n)
{
	fgets(ch, n, stdin);
	if(ch[strlen(ch)-1] == '\n')
		ch[strlen(ch)-1] = '\0';
	else
		ch[n-1] = '\0';

	if(strlen(ch) >= n-1)
		vider_buffer();
		
	#ifdef _WIN32
	system("cls");
	#endif

	#ifdef	linux
	system("clear");
	#endif
}

/* Fonction utile pour la visualisation*/
int nombre_cases_occupees(char *tab)
{
	int i, k = 0;
	for(i=0;i<N;i++)
	{
		if(tab[i]!='-')
			k++;
	}

	return k;
}



#ifdef _WIN32

void choix_couleur_joueur(joueur *js)
{
	char choix[2];
	int n;
	do
	{
		printf("Choisissez la couleur de votre pion\n");

		Color(15, 0);
	   	printf("1-Blanche(%c)\n", js->symbole);
	   	Color(15, 0);
	   	
	   	Color(8, 0);
	   	printf("2-Gris fonce(%c)\n", js->symbole);
	   	Color(15, 0);

	   	
	   	Color(9, 0);
	   	printf("3-Bleu fluo(%c)\n", js->symbole);
		Color(15, 0);

	   	Color(10, 0);
	   	printf("4-Vert fluo(%c)\n", js->symbole);
	   	Color(15, 0);

	    Color(11, 0);
	    printf("5-Turquoise(%c)\n", js->symbole);
	    Color(15, 0);

	    Color(12, 0);
	    printf("6-Rouge fluo(%c)\n", js->symbole);
	    Color(15, 0);

	    Color(13, 0);
	    printf("7-Violet(%c)\n", js->symbole);
	    Color(15, 0);

	    Color(14, 0);
	    printf("8-Jaune(%c)\n", js->symbole);
	    Color(15, 0);

	    printf("Entez la valeur: ");
	    read_c(choix, 2);
	}while(choix[0]<'1' || choix[0]>'8');

	n = atoi(choix);

	switch(n)
	{
		case 1:
			js->pion_couleur_w = 15;
		break;

		case 2:
			js->pion_couleur_w = 8;
		break;

		case 3:
			js->pion_couleur_w = 9;
		break; 

		case 4:
			js->pion_couleur_w = 10;
		break;

		case 5:
			js->pion_couleur_w = 11;
		break;

		case 6:
			js->pion_couleur_w = 12;
		break;

		case 7:
			js->pion_couleur_w = 13;
		break;  

		case 8:
			js->pion_couleur_w = 14;
		break; 

	}
}

#endif

#ifdef linux

void choix_couleur_joueur(joueur *js)
{
	char choix[2];
	int n;
	do
	{
		printf("Choisissez la couleur de votre pion\n");
	   	
	   	couleur("31");
	   	printf("1-Rouge(%c)\n", js->symbole);
	   	couleur("0");

	   	
	   	couleur("33");
	   	printf("2-Jaune(%c)\n", js->symbole);
		couleur("0");

	   	couleur("34");
	   	printf("3-Bleu Clair(%c)\n", js->symbole);
	   	couleur("0");

	    couleur("35");
	    printf("4-Violet(%c)\n", js->symbole);
	    couleur("0");

	    couleur("38");
	    printf("5-Blanc(%c)\n", js->symbole);
	    couleur("0");

	    printf("Entez la valeur: ");
	    read_c(choix, 2);
	}while(choix[0]<'1' || choix[0]>'5');

	n = atoi(choix);

	switch(n)
	{
		case 1:
			js->pion_couleur_l = 31;
		break;

		case 2:
			js->pion_couleur_l = 33;
		break; 

		case 3:
			js->pion_couleur_l = 34;
		break;

		case 4:
			js->pion_couleur_l = 35;
		break;

		case 5:
			js->pion_couleur_l = 38;
		break;

	}
}

#endif