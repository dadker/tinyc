%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
%}
%union{
    int intval;
    char *id;
    struct AST *node;
}
%start Program
%token CHAR ELSE FLOAT IF INT RETURN VOID WHILE MAIN EQ GE GT LE LT NE
%token <intval> CONSTANT;
%token <id>     ID;
%type <node> PrimaryExpression FunctionArgList FunctionCall UnaryExpression MultiplicativeExpression AdditiveExpression ComparisonExpression Expression
%type <node> AssignmentStatment IfStatement WhileStatement ReturnStatement StatementList BlockStatement EmptyStatement Statement
%type <node> ReturnType FunctionParameter FunctionParameterList VariableDefinition VariableDefinitionList FunctionStatementList FunctionBody FunctionDefinition
%type <node> FunctionDefinitionList MainFunction Program
%%
Type: INT
    | CHAR
    | FLOAT

PrimaryExpression:  CONSTANT
    | ID
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
    | MultiplicativeExpression '*' UnaryExpression 
    | MultiplicativeExpression '/' UnaryExpression 

AdditiveExpression: MultiplicativeExpression
    | AdditiveExpression '+' AdditiveExpression {$$ = addition($1, $3);}
    | AdditiveExpression '-' AdditiveExpression {$$ = subtraction($1, $3);}

ComparisonExpression:   AdditiveExpression
    | AdditiveExpression LT AdditiveExpression {$$ = lessThan($1, $3);}
    | AdditiveExpression LE AdditiveExpression {$$ = lessThanEqual($1, $3);}
    | AdditiveExpression GT AdditiveExpression {$$ = greaterThan($1, $3);}
    | AdditiveExpression GE AdditiveExpression {$$ = greaterThanEqual($1, $3);}

Expression: ComparisonExpression
    | ComparisonExpression EQ ComparisonExpression {$$ = equal($1, $3);}
    | ComparisonExpression NE ComparisonExpression {$$ = notEqual($1, $3);}

AssignmentStatment: ID '=' Expression ';' {$$ = assign($1, $3);}

IfStatement:    IF '(' Expression ')' Statement
    | IF '(' Expression ')' Statement ELSE Statement

WhileStatement: WHILE '(' Expression ')' Statement

ReturnStatement:    RETURN ';' {$$ = ret($2);}
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

VariableDefinition: Type ID '=' CONSTANT ';'

VariableDefinitionList:
    | VariableDefinition VariableDefinitionList

FunctionStatementList:  ReturnStatement
    | Statement FunctionStatementList

FunctionBody:   VariableDefinitionList FunctionStatementList

FunctionDefinition: ReturnType ID '(' FunctionParameterList ')' '{' FunctionBody '}'
    | ReturnType ID '(' VOID ')' '{' FunctionBody '}'

FunctionDefinitionList:
    | FunctionDefinition FunctionDefinitionList

Program:    FunctionDefinitionList MainFunction FunctionDefinitionList
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