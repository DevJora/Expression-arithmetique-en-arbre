%{
#include "arbre.h"
#include "y.tab.h"
#define ERREUR_LEXICO -99
int numeroLigne = 1 ;
%}
%%
\+              {return(PLUS);}
-               {return(MOINS);}
\*              {return(MULT);}
\/              {return(DIV);}
\(              {return(PO);}
\)              {return(PF);}
:=              {return(OPAFF);}
0|[1-9][0-9]*   {yylval.type2 = atoi(yytext); return(CSTE_ENTIERE);}
[a-z]           {yylval.type2 = yytext[0]; return(IDF);}
\n              {numeroLigne++;}
[ \t]           ;
.               {printf("Erreur Lexicographique : caractère %s interdit !\n",yytext);return(ERREUR_LEXICO);}
%%
int yywrap(){}