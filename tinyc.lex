%{
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
%}
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
[a-zA-Z_][a-zA-Z_0-9]*  { yylval.id = (char *) strdup(yytext); return ID;   }
"0"|[1-9][0-9]*         { yylval.val = atof(yytext); return CONSTANT;       }
[0-9]+"."[0-9]+         { yylval.val = atof(yytext); return CONSTANT;       }
\'(\\.|[^"\\])\'        { return CONSTANT;                                  }
\"(\\.|[^"\\])*\"       { return CONSTANT;                                  }
[ \t\n]+
.           { return yytext[0]; } 
%%
int yywrap(void){return 0;}

