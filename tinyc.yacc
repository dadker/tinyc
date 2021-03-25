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
%type <node> PrimaryExpression FunctionArgList FunctionCall UnaryExpression MultiplicativeExpression AdditiveExpression ComparisonExpression Expression
%type <node> AssignmentStatment IfStatement WhileStatement ReturnStatement StatementList BlockStatement EmptyStatement Statement
%type <node> ReturnType FunctionParameter FunctionParameterList VariableDefinition VariableDefinitionList FunctionStatementList FunctionBody FunctionDefinition
%type <node> FunctionDefinitionList MainFunction Program

%left  '+'  '-'
%left  '*'  '/'

%%


Type: INT
    | CHAR
    | FLOAT





PrimaryExpression:  CONSTANT                            { $$ = intLiteral($1);              }
    | ID                                                { $$ = identifier($1);              }
    | FunctionCall
    | '(' Expression ')'

FunctionArgList:    '&' ID
    | Expression
    | Expression ',' FunctionArgList

FunctionCall:   ID '(' FunctionArgList ')'
    | ID '(' ')'

UnaryExpression:    PrimaryExpression
    | '+' UnaryExpression
    | '-' UnaryExpression

MultiplicativeExpression:   UnaryExpression
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









MainFunction:   MAIN '(' VOID ')' '{' FunctionBody '}'

ReturnType: VOID
    | Type

FunctionParameter:  Type ID

FunctionParameterList:  FunctionParameter
    | FunctionParameter ',' FunctionParameterList

VariableDefinition: Type ID '=' CONSTANT ';'

VariableDefinitionList:
    | VariableDefinition VariableDefinitionList

FunctionStatementList:  ReturnStatement
    | Statement FunctionStatementList

FunctionBody:   VariableDefinitionList FunctionStatementList

FunctionDefinition: ReturnType ID '(' FunctionParameterList ')' '{' FunctionBody '}' {$$ = functionDefinition();}
    | ReturnType ID '(' VOID ')' '{' FunctionBody '}'

FunctionDefinitionList: {$$ = NULL;}
    | FunctionDefinition FunctionDefinitionList {$$ = functionList($1, $2);}

Program:    FunctionDefinitionList MainFunction FunctionDefinitionList {$$ = program($1, $2, $3);}
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