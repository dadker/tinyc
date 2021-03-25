%{
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
%}
DIGIT   [0-9]
ID      [a-z][a-z0-9]*
%%
char        { return CHAR;      }
else        { return ELSE;      }
float       { return FLOAT;     }
if          { return IF;        }
int         { return INT;       }
return      { return RETURN;    }
void        { return VOID;      }
while       { return WHILE;     }
"int main"  { return MAIN;      }
"<="        { return LE;        }
">="        { return GE;        }
"=="        { return EQ;        }
"!="        { return NE;        }
">"         { return GT;        }
"<"	        { return LT;        }
{DIGIT}+    { yylval.intValue = atoi(yytext); 
                return CONSTANT; }
{ID}        { yylval.id = (char *) strdup(yytext);
                return ID; }
[ \t\n]+
.           { return yytext[0]; } 
%%
int yywrap(void){}

