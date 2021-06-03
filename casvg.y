%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "operation.h"
#include "automate.h"
int yyerror(char*);
int yylex(void);
extern FILE *yyin;

%}

%union{
   double val;
   char* str;
}

%token CREATE REMOVE MOVE DUMP EDIT RENAME NODE EDGE 
%token FROM TO AT WITH LABEL SIZE COLOR BGCOLOR INIT 
%token FINAL NORTH WEST SOUTH EAST PATH FOREACH DO DONE 
%token IS COMPLETE DETERMINISTIC MINIMIZE SHOW EOL EOC
%token <str> DIRECTION
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
    EOL                           { }
  | Expr                          { }
  ;

Expr:
   CREATE NODE ID Attrs                       { createNode($3);setNode(); }
  | CREATE EDGE FROM ID TO ID Attrs           { createEdge($4, $6); setEdge(); }
  | REMOVE NODE ID                            { removeNode($3); }
  | REMOVE EDGE FROM ID TO ID                 { removeEdge($4, $6); }
  | MOVE Attrs                                { doMove(); }
  | RENAME ID WITH ID                         { renameObject($2,$4); }
  | EDIT ID WITH Attrs                        { editNode($2); }
  | EDIT EDGE FROM ID TO ID WITH Attrs        { editEdge($4,$6); }
  | DUMP EOL        				                  { dump(); }
  | DUMP LABELVALUE                           { dumpSVG($2); }
  | IS COMPLETE                               { printf("Is complete ? : %d \n",isComplete(getEdges(), getNodes())); }
  | COMPLETE WITH ID AT NUM NUM               { complete(getEdges(), getNodes(), $3, $5, $6); }
  | SHOW COMPLETE LABELVALUE                  { showComplete(getEdges(), getNodes(), $3); }
  | IS DETERMINISTIC                          { printf("Is determin\n"); }
  | SHOW DETERMINISTIC LABELVALUE             { /* updateNonDeterministicColor($3); */}
  | SHOW LABELVALUE                           { /*printf("%s", isAccepted($2) ? "true" : "false"); */}
  ;

Attrs:
    EOL                          { }
  | AT NUM NUM Attrs             { setPosition($2,$3); }
  | LABEL LABELVALUE Attrs       { setLabel($2); }
  | COLOR LABELVALUE Attrs       { setColor($2);}
  | BGCOLOR LABELVALUE Attrs     { setBackgroundColor($2); }
  | SIZE NUM Attrs               { setSize($2); }
  | INIT DIRECTION Attrs         { setInit($2); }
  | FINAL DIRECTION Attrs        { setFinal($2); }
  | PATH LABELVALUE Attrs        { setPath($2); }
  | ID Attrs                     { addToList($1);}
  | NUM NUM                      { move($1,$2); }
  | EOC                          { }
;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(int argc, char **argv) {
  /* Process command line args*/
  if(argc != 1){
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
  }
  yyparse();
  return 0;
}
  
