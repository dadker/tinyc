%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"
#include "AST.h"
#include "CG.h"

install (char *sym_name)
{
    symrec *s;
    s = getsym(sym_name);
    if(s == 0) s = putsym(sym_name);
    else printf("%s is already defined\n", sym_name);
}
 %}
%union{
    int intval;
    char *id;
    struct EXP *exp;
    struct STMT *stmt;
    struct FUNC *func;
    struct PROG *prog;
}
%locations
%start Program
%token CHAR ELSE FLOAT IF INT RETURN VOID WHILE MAIN EQ GE GT LE LT NE
%token <intval> CONSTANT;
%token <id>     ID;
%type <exp> PrimaryExpression FunctionArgList FunctionCall UnaryExpression MultiplicativeExpression AdditiveExpression ComparisonExpression Expression
%type <stmt> AssignmentStatment IfStatement WhileStatement ReturnStatement StatementList BlockStatement EmptyStatement Statement
%type <func> ReturnType FunctionParameter FunctionParameterList VariableDefinition VariableDefinitionList FunctionStatementList FunctionBody FunctionDefinition
%type <prog> FunctionDefinitionList MainFunction Program
%%
Type: INT
    | CHAR
    | FLOAT

PrimaryExpression:  CONSTANT { $$ = makeEXP_intLiteral($1, @1.first_line); }
    | ID    { $$ = makeEXP_identifier($1, @1.first_line); }
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
    | MultiplicativeExpression '*' UnaryExpression { $$ = makeEXP_multiplication($1, $3, @1.first_line); }
    | MultiplicativeExpression '/' UnaryExpression { $$ = makeEXP_division($1, $3, @1.first_line); }

AdditiveExpression: MultiplicativeExpression
    | AdditiveExpression '+' AdditiveExpression { $$ = makeEXP_addition($1, $3, @1.first_line); }
    | AdditiveExpression '-' AdditiveExpression { $$ = makeEXP_subtraction($1, $3, @1.first_line); }

ComparisonExpression:   AdditiveExpression
    | AdditiveExpression LT AdditiveExpression
    | AdditiveExpression LE AdditiveExpression
    | AdditiveExpression GT AdditiveExpression
    | AdditiveExpression GE AdditiveExpression

Expression: ComparisonExpression
    | ComparisonExpression EQ ComparisonExpression
    | ComparisonExpression NE ComparisonExpression

AssignmentStatment: ID '=' Expression ';'

IfStatement:    IF '(' Expression ')' Statement
    | IF '(' Expression ')' Statement ELSE Statement

WhileStatement: WHILE '(' Expression ')' Statement

ReturnStatement:    RETURN ';'
    | RETURN Expression ';'

StatementList:
    | Statement StatementList

BlockStatement: '{' StatementList '}'

EmptyStatement: ';'

Statement:  AssignmentStatment
    | IfStatement
    | WhileStatement
    | ReturnStatement
    | BlockStatement
    | EmptyStatement

MainFunction:   MAIN '(' VOID ')' '{' FunctionBody '}'

ReturnType: VOID
    | Type

FunctionParameter:  Type ID

FunctionParameterList:  FunctionParameter
    | FunctionParameter ',' FunctionParameterList

VariableDefinition: Type ID '=' CONSTANT ';' { install($2); }

VariableDefinitionList:
    | VariableDefinition VariableDefinitionList

FunctionStatementList:  ReturnStatement
    | Statement FunctionStatementList

FunctionBody:   VariableDefinitionList FunctionStatementList

FunctionDefinition: ReturnType ID '(' FunctionParameterList ')' '{' FunctionBody '}' { install($2); }
    | ReturnType ID '(' VOID ')' '{' FunctionBody '}' { install($2); }

FunctionDefinitionList:
    | FunctionDefinition FunctionDefinitionList

Program:    FunctionDefinitionList MainFunction FunctionDefinitionList
%% 
int lineno;
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