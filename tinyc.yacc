%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
%}

%union{
    int intValue;
    char* id;
    struct AST *node;
}

%start Program
%token CHAR ELSE FLOAT IF INT RETURN VOID WHILE MAIN EQ GE GT LE LT NE
%token <intValue> CONSTANT
%token <id> ID
%type <node> FunctionArgList UnaryExpression MultiplicativeExpression AdditiveExpression ComparisonExpression Expression
%type <node> Statement
%type <node> ReturnType FunctionParameter FunctionParameterList VariableDefinition VariableDefinitionList FunctionStatementList FunctionBody FunctionDefinition
%type <node> FunctionDefinitionList MainFunction Program

%left  '+'  '-'
%left  '*'  '/'

%%

FunctionArgList: '&' ID                                 {                                   }
    | Expression                                        {                                   }
    | Expression ',' FunctionArgList                    {                                   }

UnaryExpression: CONSTANT                               { $$ = intLiteral($1);              }
    | ID                                                { $$ = identifier($1);              }
    | FunctionCall                                      {                                   }
    | ID '(' FunctionArgList ')'                        {                                   }
    | ID '(' ')'                                        {                                   }
    | '(' Expression ')'                                {                                   }
    | '+' UnaryExpression                               {                                   }
    | '-' UnaryExpression                               {                                   }

MultiplicativeExpression: UnaryExpression               {                                   }
    | MultiplicativeExpression '*' UnaryExpression      { $$ = multiply($1, $3);            }
    | MultiplicativeExpression '/' UnaryExpression      { $$ = divide($1, $3);              }

AdditiveExpression: MultiplicativeExpression
    | AdditiveExpression '+' AdditiveExpression         { $$ = addition($1, $3);            }
    | AdditiveExpression '-' AdditiveExpression         { $$ = subtraction($1, $3);         }

ComparisonExpression:   AdditiveExpression
    | AdditiveExpression LT AdditiveExpression          { $$ = lessThan($1, $3);            }
    | AdditiveExpression LE AdditiveExpression          { $$ = lessThanEqual($1, $3);       }
    | AdditiveExpression GT AdditiveExpression          { $$ = greaterThan($1, $3);         }
    | AdditiveExpression GE AdditiveExpression          { $$ = greaterThanEqual($1, $3);    }

Expression: ComparisonExpression
    | ComparisonExpression EQ ComparisonExpression      { $$ = equal($1, $3);               }
    | ComparisonExpression NE ComparisonExpression      { $$ = notEqual($1, $3);            }





StatementList:                                          { $$ = NULL                         }
    | Statement StatementList                           { $$ = statementList($1, $2);       }

Statement:  ID '=' Expression ';'                       { $$ = assign($1, $3);              }
    | IF '(' Expression ')' Statement                   { $$ = ifStatement($3, $5);         }
    | IF '(' Expression ')' Statement ELSE Statement    { $$ = ifElseStatement($3, $5, $7); }
    | WHILE '(' Expression ')' Statement                { $$ = whileStatement($3, $5);      }
    | RETURN ';'                                        {                                   }
    | RETURN Expression ';'                             { $$ = ret($2);                     }
    | '{' StatementList '}'                             {                                   }
    | ;                                                 {                                   }









ReturnType: VOID
    | INT
    | CHAR
    | FLOAT

FunctionParameterList: INT ID
    | CHAR ID
    | FLOAT ID
    | INT ID ',' FunctionParameterList
    | CHAR ID ',' FunctionParameterList
    | FLOAT ID ',' FunctionParameterList

VariableDefinitionList:
    | INT ID '=' CONSTANT ';' VariableDefinitionList
    | CHAR ID '=' CONSTANT ';' VariableDefinitionList
    | FLOAT ID '=' CONSTANT ';' VariableDefinitionList

FunctionStatementList: RETURN ';'
    | RETURN Expression ';'
    | Statement FunctionStatementList  

FunctionDefinition: ReturnType ID '(' FunctionParameterList ')' '{' VariableDefinitionList FunctionStatementList '}'    {$$ = functionDefinition();}
    | ReturnType ID '(' VOID ')' '{' VariableDefinitionList FunctionStatementList '}'



FunctionDefinitionList:                                                                 {$$ = NULL;}
    | FunctionDefinition FunctionDefinitionList {$$ = functionList($1, $2);}

MainFunction: MAIN '(' VOID ')' '{' VariableDefinitionList FunctionStatementList '}'

Program:    FunctionDefinitionList MainFunction FunctionDefinitionList                  {$$ = program($1, $2, $3);}

%% 


int main(int argc, char** argv)
{   extern FILE *yyin;
    ++argv; --argc;
    yyin = fopen(argv[0], "r");
    yyparse();
    printf("Parse Completed\n");
} 

int yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n",str);
}