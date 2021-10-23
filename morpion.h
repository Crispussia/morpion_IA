#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef COULEURS
#define COULEURS
#define clrscr() printf ("\033[H\033[2j")
#endif
#define couleur(param) printf ("\033[%sm",param)


#define N 9
typedef struct joueur
{
	char nom[20];
	char symbole;
	int score;
	int pion_couleur_w;
	int pion_couleur_l;
  	
}joueur;


typedef struct info //structure pour retenir les statistiques d'un joueur
{
	char nom[20];
	int nb_parties; //nombre de parties jouées
	int nb_parties_g; //nombre de parties gagnées
	int nb_parties_p; //nombre de parties perdues
	int nb_parties_a; //nombre de parties annulées
	int nb_parties_n; //nombre de parties nulles
	char parties_s[200];

}infos;

void init_table(char *table);
#ifdef linux
void affiche_table(char *table,joueur **js);
void affichecouleur(char c, joueur**js);
void choix_couleur_joueur(joueur *js);
#endif 

#ifdef _WIN32
void affiche_table(char *table,joueur **js);
void affichcouleur(char c,joueur**js);
void Color(int couleurDuTexte,int couleurDeFond);
void choix_couleur_joueur(joueur *js);
#endif

joueur *creer_joueur();
joueur** init_joueurs_perso();
int statut_jeu(char *tab, joueur **js);
int si_case_occupee(char *tab, int pos);
void debut_jeu(joueur **js, char *tab);
void debut_jeu1(joueur **js, char *tab);
void lancer_partie(char*tab,joueur **js, int NIVEAU);
void visualiser_partie();



/*fonctions utilitaire.c*/
int si_X_O(char *s);
int si_alpha(char *s);
char caractere_IA (char c_joueur);
int si_nombre(char *s);
int si_oui_non(char *s);
void vider_buffer();
void read_c(char *ch, int n);
int nombre_cases_occupees(char *tab);
int maxi(int a, int b);

/*fonctions ia.c*/
joueur** init_joueur_ia_perso();
void j_vs_ia1(joueur **js, char *tab);
int pos_aleatoire(char *tab);
void tour_ia2(joueur **js, char *tab);
void j_vs_ia2(joueur **js, char *tab);
int position_perdante(joueur **js,char *tab);
void tour_ia3(joueur **js, char *tab);
void j_vs_ia3(joueur **js, char *tab);
int position_gagnante(joueur **js,char *tab);
int min_max (char *tab,joueur **js,char j);
void tour_ia4(char *tab,joueur **js);
void j_vs_ia4(joueur **js, char *tab);


/*fonctions sauvegarde.c*/
void save_auto(FILE *f, char *tab, int n);
int charger_partie(char tab[],int n, joueur** js, int* NIVEAU);
int si_partie_existe (char *nom);
void ajout_nom (char* nom);
int sauvegarde (FILE *g, char tab[], int n, joueur** js, int NIVEAU, infos *player);

/*fonctions statistiques*/
int rechercher_joueur(infos *player);
infos* creer_infos(char *nom);
void set_nb_parties(infos *player);
void set_nb_parties_g(infos *player);
void set_nb_parties_p(infos *player);
void set_nb_parties_a(infos *player);
void set_nb_parties_n(infos *player);
void set_nb_parties_s(infos *player, char *nom_backup);
void update_statistiques(infos *p); 
void afficher_statistiques();

/*fonction menu*/
void aide ();
void menu1();
void menu2();
void menu3();
void menujoueurIA();
void menu_newpartie();
void menu();




