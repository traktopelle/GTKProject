#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include <stdlib.h>
#include <gtk/gtk.h>

///constantes

#define XMAX 12 //Largeux du tableau, à utiliser dans les boucles etc... (ne jamais mettre de valeur en "dur" (par exemple  au lieu de mettre i<12, mettre i<XMAX)).
#define YMAX 8//Hauteur du tableau

#define C_FORME_AUTORISEE 1
#define C_FORME_REFUSEE 0

#define C_CYCLE_VRAI 1
#define C_CYCLE_FAUX 0

#define C_NIVEAU_TRACE 0
#define C_NB_CARTE 80
#define C_TAILLE_MAX 1000


///definition de types
typedef struct Forme //Structure utilisée lors de la création d'une nouvelle forme (pioche) et dans mon tableau de jeu
{
    int haut;
    int bas;
    int droite;
    int gauche;
    int tourne;
    int marque;
}s_forme;

typedef struct maillon // Structure interne à la liste chainée
{
    int x;
    int y;
    struct maillon* suivant;
}s_maillon;

typedef struct pile // De même
{
    int longueur;
    struct maillon* debut;
}s_pile;

typedef struct stockee // De même
{
    int x_stocke;
    int y_stocke;
}t_stockee;


typedef struct affichage_jeu
{
    GtkWidget* vbox;  //vbox contenant la hbox score et le tableau de jeu
    GtkWidget* table; // table de jeu
    GtkWidget* table_score; // table score actuel
    GtkWidget* table_score_tot; // table score total
    GtkWidget* vpioche; // vertival box contenant nb de carte, bouton tourner et l'image de la pioche
    GtkWidget* hbox;    // hbox d(afficha de vpioche et des tables score
    GtkWidget* image; // image de la pioche
    GtkWidget* btn_tourner; // bouton tourner
    GtkWidget* btn_tab_jeu[XMAX][YMAX];
    GtkWidget* pLabel_score_act;
    GtkWidget* pLabel_score_tot;
    GtkWidget* pnb_carte;
    GtkWidget* pwin_tableau_jeu;

}affiche;

typedef struct position //Structure data ou sont stockés l'x et y du bouton lors du g_signal_connect (comme dans l'exemple2 du cours GTK)
{
    int x;
    int y;
}s_position_evenement;

typedef struct jeu_tot
{
    int score_actuel;//score de la derniere boucle fermée
    int score_total; //Score total, déclaré en variable globale (Accessible partout)
    int nbpioche;
    s_forme* forme_cree; //Forme créée dans la pioche, déclaré en variable globale
    affiche* aff;//structure permettant de mettre a jour l'affichage après chaque clic.
}jeu_tot;



///prototypes

void creerwin(jeu_tot* jeu);
void creertable(jeu_tot* jeu);
void creerhbox(jeu_tot* jeu);

GtkWidget* creernbpioche(jeu_tot* jeu);

void tourne(GtkWidget* sender,jeu_tot* jeu);

void lancer_nouvelle_partie();
void initialiser_nouvelle_variable(jeu_tot* jeu);
//void fermer_fenetre(GtkWidget* sender,jeu_tot* jeu);
void fermer_fenetre(GtkButton* sender,GtkWidget* pFormulaire);
void sauver(GtkWidget* sender,jeu_tot* jeu);
void initialiser_variable(jeu_tot* jeu);
void reprendrepartie();


char* associer_fichier_image (int haut,int bas,int gauche,int droite);
void lancer_nouvelle_partie();
void reprendrepartie();
void on_clique_table(GtkWidget* sender,s_position_evenement* xy_case );
void creerimage(jeu_tot*jeu);
void creerforme(jeu_tot*jeu);
void affiche_vue_instruction();
void empiler(s_pile* p_pile, s_position_evenement s_position );
#endif // PROTOTYPE_H_INCLUDED
