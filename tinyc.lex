%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
extern int line_num;
char ch_arr[10][100];
int numStrings = 0;
%}
%option noyywrap
%%
char        { return CHAR;      }
else        { return ELSE;      }
float       { return FLOAT;     }
if          { return IF;        }
int         { return INT;       }
return      { return RETURN;    }
void        { return VOID;      }
while       { return WHILE;     }
printf      { return PRINTF;    }
scanf       { return SCANF;     }
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
\"(\\.|[^"\\])*\"       { strcpy(ch_arr[numStrings], yytext); numStrings++; return CONSTANT; }
[ \t]+
\n          { line_num++; }
.           { return yytext[0]; } 
%%
int printStrings() 
{
    for (int i = 0; i < numStrings; i++ )
    {
        printf(".LC%d:\n\t.string %s\n\n", i, ch_arr[i]);
    }
}