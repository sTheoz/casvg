%{
      #include "casvg.tab.h"
      #include <stdlib.h>
      #include <ctype.h>
      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>

%}

create_regex	    (?i:create)
remove_regex	    (?i:remove)
move_regex	          (?i:move)
dump_regex	          (?i:dump)
edit_regex	          (?i:edit)
rename_regex	    (?i:rename)
node_regex	          (?i:node)
edge_regex	          (?i:edge)
from_regex	          (?i:from)
to_regex	          (?i:to)
at_regex	          (?i:at)
with_regex	          (?i:with)
label_regex	          (?i:label)
size_regex	          (?i:size)
color_regex	          (?i:color)
bgcolor_regex	    (?i:bgcolor)
initial_regex	    (?i:initial)
final_regex	          (?i:final)
path_regex	          (?i:path)
foreach_regex	    (?i:foreach)
do_regex	          (?i:do)
done_regex	          (?i:done)
is_regex	          (?i:is)
complete_regex	    (?i:complete)
deterministic_regex   (?i:deterministic)
minimize_regex	    (?i:minimize)
show_regex	          (?i:show)
direction_regex       (?i:north)|(?i:south)|(?i:east)|(?i:west)


id			      ([a-zA-Z_0-9]{1,15})
num                     [0-9]+
label                   \"([^"\\]*(\\.[^"\\]*)*)\"

%%

{create_regex}          { return CREATE; }
{remove_regex}          { return REMOVE; }
{move_regex}            { return MOVE; }
{dump_regex}            { return DUMP; }
{edit_regex}            { return EDIT; }
{rename_regex}          { return RENAME; }
{node_regex}            { return NODE; }
{edge_regex}            { return EDGE; }
{from_regex}            { return FROM; }
{to_regex}              { return TO; }
{at_regex}              { return AT; }
{with_regex}            { return WITH; }
{label_regex}           { return LABEL; }
{size_regex}            { return SIZE; }
{color_regex}           { return COLOR; }
{bgcolor_regex}         { return BGCOLOR; }
{initial_regex}         { return INIT; }
{final_regex}           { return FINAL; }

{path_regex}            { return PATH; }
{foreach_regex}         { return FOREACH; }
{do_regex}              { return DO; }
{done_regex}            { return DONE; }
{is_regex}              { return IS; }
{complete_regex}        { return COMPLETE; }
{deterministic_regex}   { return DETERMINISTIC; }
{minimize_regex}        { return MINIMIZE; }
{show_regex}            { return SHOW; }

{direction_regex}     { 
      yylval.str = strdup(yytext);
      return DIRECTION; 
}

{num} {
      yylval.val = strtoul(yytext, NULL, 10);
      return NUM;
}
{id} {
      yylval.str = strdup(yytext);
      return ID;
}
{label} {
      char* l = strdup(yytext);
      l = l+1;
      l[strlen(l)-1] = '\0';
      yylval.str = l;
      return LABELVALUE;
}

"\n"  { return EOL; }

.     { /* On ignore */ }
