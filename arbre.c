#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

/*Retourne un pointeur fils du pere*/
Arbre concatPereFils(Arbre pere, Arbre fils){
    if(fils==NULL)
        return pere;
    
    pere->gauche = fils;

    return pere;
}

/*Retourne un pointeur frere du pere*/
Arbre concatPereFrere(Arbre pere, Arbre frere) {
    if(frere == NULL)
        return pere;
    
    pere->droit = frere;
}

/*Cree un noeud*/
Arbre creerNoeud(int nature, int valeur)
{
    Arbre noeud;
    noeud = (Arbre) malloc(sizeof(noeud));
    if(noeud == NULL)
    {
        printf("malloc: erreur d'allocation memoire");
        return NULL;
    }
    //noeud = (Arbre)xmalloc(1, sizeof(Noeud));
    noeud->valeur = valeur;
    noeud->nature = nature;
    return noeud;
}


/*mibere la mémoire*/
void libererArbre(Arbre a){
    if(a != NULL) {
        libererArbre(a->gauche);
        libererArbre(a->droit);
        free(a);

    }
}

/*renvoie le define correspondant à l'entier*/
char *remplacerEniterParDefine(int n){
    switch (n)
    {
    case 3:
        return "A_AFFECT";
        break;
    case 4:
        return "A_PLUS";
        break;
    case 5:
        return "A_MOINS";
        break;
    case 6:
        return "A_MULT";
        break;
    case 2:
        return "A_CSTE_ENTIER";
        break;
    case 1:
        return "A_IDF";
        break;
 break;

    default:
        return "Element invalide";
        break;
    }
}

/*Fonction d'affichage*/
void afficher_arbre(Arbre a, int tabulation){
    printf("\n\t Arbre d'instructions : ");
    int i;
    printf("[%s|%d]", remplacerEniterParDefine(a->nature), a->valeur);

    if(a->gauche != NULL){
        printf("\n\t");
        for(i=0; i<tabulation; i++)
            printf(" ");
        
        afficher_arbre(a->gauche, ++tabulation);
    }

    if(a->droit != NULL){
        printf("\n\t");
        
        afficher_arbre(a->droit, ++tabulation);
        printf("\n");
    }
}

/*verifie si le noeud est une feuille*/
booleen estFeuille(Arbre a){
    if(a->droit == NULL && a->gauche == NULL)
        return VRAI;
    else 
        return FAUX;
}

int evaluationPostfixee(Arbre a){
	if ( a != NULL ){
		//si c'est un opérateur
		if (estOperateur(a->nature)){ 

			int operande_gauche = evaluationPostfixee( a->gauche );
			int operande_droite = evaluationPostfixee( a->droit );

			switch (a->valeur) {
				case A_PLUS :
					return operande_gauche + operande_droite;
					break;
				case A_MOINS :
					return operande_gauche - operande_droite;
					break;
				case A_MULT :
					return operande_gauche * operande_droite;
					break;
				case A_DIV :
					return operande_gauche / operande_droite;
					break;
			}
		
		/* 
		* Si on a un opÃ©rande : on retourne sa valeur 
		*/
		} else { 

			// Pas de typage fort en C, l'info est de type char et en int Ã  pour valeur son code ASCII
			return a->valeur;
 
		}
	}
}


int caracVersEntier( char c ){
	char temp[2];
	sprintf(temp,"%c",c); // Mettre dans un char* le caractÃ¨re avant de le passer Ã  atoi
	return atoi(temp);
}

//verifie si c'est un operateur 
booleen estOperateur( int c ){
	switch (c) {
		case 4 :
			return VRAI;
			break;
		case 5 :
			return VRAI;
			break;
		case 6 :
			return VRAI;
			break;
		case 7 :
			return VRAI;
			break;
		default :
			return FAUX;
			break;
	}
}


Arbre arbreDerive( Arbre racine ){

	if ( racine != NULL ){
        //si feuille
		if (!estOperateur(racine->nature)){ 

			///Si le noeud est un entier
			if ( racine->nature == A_CSTE_ENTIERE)
				return creerNoeud(A_CSTE_ENTIERE, 0);
			//si le noeud est une variable (ex: x)
			if (racine->nature == A_IDF )
				return creerNoeud(A_CSTE_ENTIERE, 1);

		//si c'est un operateur
		} else if ( estOperateur(racine->nature ) ){ 

			Arbre nouva, sag, sad, noeudMulGauche, noeudMulDroit , up, vp, noeudSubGauche, noeudMulCarre;

			// DiffÃ©rentes constructions selon l'opÃ©rateur
			switch ( racine->nature){

				// (u+v)' = u' + v'
				case A_PLUS :
					// Recopie du noeud de l'arbre de base vers un arbre pour l'expression dÃ©rivÃ©e
					nouva = creerNoeud(A_PLUS, -1);
					// DÃ©rivations des sous-arbres gauche et droit
					sag = arbreDerive(racine->gauche);
					sad = arbreDerive(racine->droit);
					nouva->gauche = sag;
					nouva->droit = sad;
					break;
				// (u-v)' = u' - v'
				case A_MOINS :
					// Recopie du noeud de l'arbre de base vers un arbre pour l'expression dÃ©rivÃ©e
					nouva = creerNoeud(A_MOINS, -1);
					// DÃ©rivations des sous-arbres gauche et droit
					sag = arbreDerive(racine->gauche);
					sad = arbreDerive(racine->droit);
					nouva->gauche = sag;
					nouva->droit = sad;						
					break;
				// (uv)' = u'v + v'u
				case A_MULT :
					// Creation d'un noeud avec un +
					nouva = creerNoeud(A_MULT, -1);
					// Creations des deux noeuds avec un *
					noeudMulGauche = creerNoeud(A_MULT, -1);
					nouva->gauche = noeudMulGauche;
					noeudMulDroit = creerNoeud(A_MULT, -1);
					nouva->droit = noeudMulDroit;
					// Ajout des noeuds pour les variables
					noeudMulGauche->gauche = racine->gauche;
					up = arbreDerive(racine->droit);
					noeudMulGauche->droit = up;
					vp = arbreDerive(racine->gauche);
					noeudMulDroit->gauche = vp;
					noeudMulDroit->droit = racine->droit;
					break;
				// (u/v)' = (u'v - v'u) / v²
				case A_DIV :
					// Creation d'un noeud avec un /
					nouva = creerNoeud(A_DIV, -1);
					// Creation du noeud avec un -
					noeudSubGauche = creerNoeud(A_MOINS, -1);
					// Creations des noeuds avec un *
					noeudMulGauche = creerNoeud(A_MULT, -1);
					noeudMulDroit = creerNoeud(A_MULT, -1);
					// Affectations des sous-arbres
					up = arbreDerive(racine->gauche);
					noeudMulGauche->gauche = up;
					noeudMulGauche->droit = racine->droit;
					noeudMulDroit->gauche = racine->gauche;
					vp = arbreDerive(racine->droit);
					noeudMulDroit->droit = vp;
					// Creation du noeud pour vÂ²
					noeudMulCarre = creerNoeud(A_MULT, -1);
					noeudMulCarre->gauche = racine->droit;	
					noeudMulCarre->droit = racine->droit;
					break;
				default :
					break;

			}

			return nouva;
		}

	}
}
