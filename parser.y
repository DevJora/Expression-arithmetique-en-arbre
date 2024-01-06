%{
#include <stdio.h>
#include "arbre.h"
int yylex();
int yyerror();
extern int numeroLigne;
%}
%union{
arbre type1;
int type2;
}
%token PLUS MOINS MULT DIV
%token PO PF
%token OPAFF
%token <type2> CSTE_ENTIERE IDF
%type <type1> affectation e1 e2 e3
%%
ligne : affectation { printf("Arbre de l'instruction :\n") ;
afficher_arbre($1, 0) ; printf("result = %d\n", evaluationPostfixee($1)); afficher_arbre(arbreDerive($1), 0);}
;
affectation : IDF OPAFF e1
{$$ = concatPereFils(creerNoeud(A_AFFECT,-1),
concatPereFrere(creerNoeud(A_IDF,$1),
$3));}
;
e1 : e1 PLUS e2 {$$=concatPereFils(creerNoeud(A_PLUS,-1), concatPereFrere($1,$3));}
| e1 MOINS e2   {$$=concatPereFils(creerNoeud(A_MOINS,-1),concatPereFrere($1,$3));}
| e2            {$$ = $1;}
;
e2 : e2 MULT e3 {$$=concatPereFils(creerNoeud(A_MULT,-1),concatPereFrere($1,$3));}
| e2 DIV e3     {$$=concatPereFils(creerNoeud(A_DIV,-1),concatPereFrere($1,$3));}
| e3            {$$ = $1;}
;
e3 : PO e1 PF   {$$ = $2;}
| CSTE_ENTIERE  {$$ = creerNoeud(A_CSTE_ENTIERE,$1);}
| IDF           {$$ = creerNoeud(A_IDF,$1);}
;



%%
int yyerror(){
printf("Erreur de syntaxe en ligne %d\n", numeroLigne);
}
int main(){
yyparse();
}