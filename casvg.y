%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "automate.h"
int yyerror(char*);
int yylex(void);

%}

%union{
   long val;
   char* str;
}

%token CREATE REMOVE MOVE DUMP EDIT RENAME NODE EDGE 
%token FROM TO AT WITH LABEL SIZE COLOR BGCOLOR INITIAL 
%token FINAL NORTH WEST SOUTH EAST PATH FOREACH DO DONE 
%token IS COMPLETE DETERMINISTIC MINIMIZE SHOW EOL
%token ID NUM LABELVALUE

%type <str> Expr
%type <str> Attrs
%type <str> ID
%type <val> NUM
%type <str> LABELVALUE

%start S

%%

S:
    Line                          { }
  | S Line                        { }
  ;

Line:
    EOL                           { printf("EOL\n"); }
  | Expr                          { /*printf("Resultat : %lu\n",$1);*/ }
  ;

Expr:
   CREATE NODE ID Attrs                      { createNode($3);setNode(); }
  | CREATE EDGE FROM ID TO ID Attrs           { createEdge($4, $6); setEdge(); }
  | REMOVE NODE ID                            { removeNode($3); }
  | REMOVE EDGE FROM ID TO ID                 { removeEdge($4, $6); }
  | MOVE Attrs                                { doMove(); }
  | RENAME ID WITH ID                         { printf("Create node\n");/*RenameNode($2, $4);*/}
  | EDIT ID WITH Attrs                        { printf("Create node\n");/*EditNode($2);*/}
  | EDIT EDGE FROM ID TO ID WITH Attrs        { printf("Create node\n");/*EditEdge($4, $6);*/}
  | DUMP EOL        				                  { dump(); }
  | DUMP LABELVALUE                           { dumpSVG($2); }
  ;

Attrs:
    EOL                          { printf("Terminus\n");}
  | AT NUM NUM Attrs             { setPosition($2,$3); }
  | LABEL LABELVALUE Attrs       { setLabel($2); }
  | COLOR LABELVALUE Attrs       { setColor($2);}
  | BGCOLOR LABELVALUE Attrs     { setBackgroundColor($2); }
  | SIZE NUM Attrs               { setSize($2); }
  | INITIAL LABELVALUE Attrs     { setInitial($2); }
  | FINAL LABELVALUE Attrs       { setFinal($2); }
  | PATH LABELVALUE Attrs        { setPath($2); }
  | ID Attrs                     { addToList($1);}
  | NUM NUM                      { move($1,$2); }

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}
