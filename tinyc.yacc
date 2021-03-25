%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

int yylex();
int yyerror(const char* s);
%}

%union{
    int intValue;
    char* id;
    struct AST *node;
}

%token CHAR ELSE FLOAT IF INT RETURN VOID WHILE MAIN EQ NE LT LE GT GE
%token <intValue> CONSTANT
%token <id> ID
%type <node> FunctionArgList UnaryExpression MultiplicativeExpression AdditiveExpression ComparisonExpression Expression
%type <node> AssignmentStatment IfStatement WhileStatement ReturnStatement StatementList BlockStatement EmptyStatement Statement
%type <node> Type ReturnType FunctionParameter FunctionParameterList VariableDefinition VariableDefinitionList FunctionStatementList FunctionBody FunctionDefinition
%type <node> FunctionDefinitionList MainFunction Program
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left  '+'  '-'
%left  '*'  '/'
%start Program

%%

FunctionArgList: '&' ID                                                     { $$ = amp(identifier($2));         }                        
    | Expression                                        
    | Expression ',' FunctionArgList                                        { $$ = argList($1, $3);             }

UnaryExpression: CONSTANT                                                   { $$ = intLiteral($1);              }
    | ID                                                                    { $$ = identifier($1);              }
    | ID '(' FunctionArgList ')'                                            { $$ = args(identifier($1), $3);    }
    | ID '(' ')'                                                            { $$ = noArgs(identifier($1));      }
    | '(' Expression ')'                                                    { $$ = parens($2);                  }
    | '+' UnaryExpression                                                   { $$ = positive($2);                }
    | '-' UnaryExpression                                                   { $$ = negative($2);                }

MultiplicativeExpression: UnaryExpression                                                  
    | MultiplicativeExpression '*' UnaryExpression                          { $$ = multiply($1, $3);            }
    | MultiplicativeExpression '/' UnaryExpression                          { $$ = divide($1, $3);              }

AdditiveExpression: MultiplicativeExpression
    | AdditiveExpression '+' AdditiveExpression                             { $$ = addition($1, $3);            }
    | AdditiveExpression '-' AdditiveExpression                             { $$ = subtraction($1, $3);         }

ComparisonExpression:   AdditiveExpression
    | AdditiveExpression LT AdditiveExpression                              { $$ = lessThan($1, $3);            }
    | AdditiveExpression LE AdditiveExpression                              { $$ = lessThanEqual($1, $3);       }
    | AdditiveExpression GT AdditiveExpression                              { $$ = greaterThan($1, $3);         }
    | AdditiveExpression GE AdditiveExpression                              { $$ = greaterThanEqual($1, $3);    }

Expression: ComparisonExpression                        
    | ComparisonExpression EQ ComparisonExpression                          { $$ = equal($1, $3);               }
    | ComparisonExpression NE ComparisonExpression                          { $$ = notEqual($1, $3);            }

AssignmentStatment: ID '=' Expression ';'                                   { $$ = assign(identifier($1), $3);  }

IfStatement: IF '(' Expression ')' Statement %prec LOWER_THAN_ELSE          { $$ = ifStatement($3, $5);         }
    | IF '(' Expression ')' Statement ELSE Statement                        { $$ = ifElseStatement($3, $5, $7); }

WhileStatement: WHILE '(' Expression ')' Statement                          { $$ = whileStatement($3, $5);      }

ReturnStatement: RETURN ';'                                                 { $$ = ret();                       }
    | RETURN Expression ';'                                                 { $$ = retExp($2);                  }

StatementList:                                                              { $$ = NULL;                        }
    | Statement StatementList                                               { $$ = statementList($1, $2);       }

BlockStatement: '{' StatementList '}'                                       { $$ = block($2);                   }

EmptyStatement: ';'                                                         { $$ = empty();                     }

Statement: AssignmentStatment
    | IfStatement
    | WhileStatement
    | ReturnStatement
    | BlockStatement
    | EmptyStatement

Type: INT                                                                   { $$ = typeInt();                   }                                                             
    | CHAR                                                                  { $$ = typeChar();                  }  
    | FLOAT                                                                 { $$ = typeFloat();                 }  

ReturnType: VOID                                                            { $$ = typeVoid();                  }
    | Type

FunctionParameter: Type ID                                                  { $$ = param($1, identifier($2));   }

FunctionParameterList: FunctionParameter                                    
    | FunctionParameter ',' FunctionParameterList                           { $$ = paramList($1, $3);           }

VariableDefinition: Type ID '=' CONSTANT ';'                                { $$ = def($1, identifier($2), intLiteral($4)); }

VariableDefinitionList:                                                     { $$ = NULL;                        }
    | VariableDefinition VariableDefinitionList                             { $$ = varList($1, $2);             }

FunctionStatementList: ReturnStatement                                      
    | Statement FunctionStatementList                                       { $$ = functionStatementList($1, $2); }

FunctionBody: VariableDefinitionList FunctionStatementList                  { $$ = functionBody($1, $2);        }

FunctionDefinition: ReturnType ID '(' FunctionParameterList ')' '{' FunctionBody '}'        { $$ = functionDefinition($1, identifier($2), $4, $7);}
    | ReturnType ID '(' VOID ')' '{' FunctionBody '}'                                       { $$ = voidFunction($1, identifier($2), $7); }

FunctionDefinitionList:                                                     { $$ = NULL;                        }
    | FunctionDefinition FunctionDefinitionList                             { $$ = functionDefinitionList($1, $2);}

MainFunction: MAIN '(' VOID ')' '{' FunctionBody '}'                    { $$ = mainFunction($6);            }

Program: FunctionDefinitionList MainFunction FunctionDefinitionList         { $$ = program($1, $2, $3);         }

%%

int main(int argc, char** argv)
{   extern FILE *yyin;
    ++argv; --argc;
    yyin = fopen(argv[0], "r");
    yyparse();
} 

int yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n",str);
}