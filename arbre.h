#define A_IDF 1
#define A_CSTE_ENTIERE 2
#define A_AFFECT 3
#define A_PLUS 4
#define A_MOINS 5
#define A_MULT 6
#define A_DIV 7

typedef struct noeud{
int nature;
int valeur;
struct noeud *gauche;
struct noeud *droit;
} noeud, *Arbre ;

/*-------Booléen----*/
typedef enum {
	FAUX = 0,
	VRAI = 1
} booleen;

typedef struct noeud * arbre;
arbre concatPereFils(arbre pere, arbre fils);
arbre concatPereFrere(arbre pere, arbre frere);
arbre creerNoeud(int nature, int valeur);
void afficher_arbre(Arbre a, int tabulation);
booleen estOperateur( int c );
int evaluationPostfixee(Arbre a);
booleen estChiffre( int c );
Arbre arbreDerive( Arbre racine );