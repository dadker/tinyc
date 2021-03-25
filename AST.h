typedef struct AST AST;

struct AST {
    enum {k_amp, k_argList, k_IntLiteral, k_Identifier, k_args, k_noArgs, k_parens, k_positive, 
    k_negative, k_multiply, k_divide, k_addition, k_subtraction, k_lessThan, k_lessThanEqual, 
    k_greaterThan, k_greaterThanEqual, k_equal, k_notEqual, k_assign, k_if, k_ifElse, k_while, 
    k_ret, k_retExp, k_statementList, k_block, k_empty, k_typeInt, k_typeChar, k_typeFloat, 
    k_param, k_paramList, k_varList, k_functionStatementList, k_functionDefinition, k_voidFunction,
    k_functionDefinitionList, k_mainFunction, k_program, k_typeVoid, k_def, k_functionBody} kind;
    union {
        char *identifier;
        int intLiteral;
        struct { AST *lhs; AST *rhs; } binary;
        struct { AST *lhs; AST *mhs; AST *rhs; } trinary;
        struct { AST *lhs; AST *mlhs; AST *mrhs; AST *rhs; } quad;
    } val;
};

AST *amp(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_amp;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *argList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_argList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *intLiteral(int intLiteral)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_IntLiteral;
    e->val.intLiteral = intLiteral;
    return e;
}

AST *identifier(char* identifier)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_Identifier;
    e->val.identifier = identifier;
    return e;
}

AST *args(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_args;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *noArgs(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_noArgs;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *parens(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_parens;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *positive(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_positive;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *negative(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_negative;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *multiply(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_multiply;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *divide(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_divide;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *addition(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_addition;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *subtraction(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_subtraction;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *lessThan(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_lessThan;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *lessThanEqual(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_lessThanEqual;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *greaterThan(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_greaterThan;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *greaterThanEqual(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_greaterThanEqual;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *equal(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_equal;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *notEqual(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_notEqual;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *assign(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_assign;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *ifStatement(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_if;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *ifElseStatement(AST *node1, AST *node2, AST *node3)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_ifElse;
    e->val.trinary.lhs = node1;
    e->val.trinary.mhs = node2;
    e->val.trinary.rhs = node3;
    return e;
}

AST *whileStatement(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_while;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *ret()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_ret;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *retExp(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_retExp;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *statementList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_statementList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *block(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_block;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *empty()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_empty;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *typeInt()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_typeInt;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *typeChar()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_typeChar;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *typeFloat()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_typeFloat;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *param(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_param;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *paramList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_paramList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *varList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_varList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *functionStatementList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_functionStatementList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *functionDefinition(AST *node1, AST *node2, AST *node3, AST *node4)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_functionDefinition;
    e->val.quad.lhs = node1;
    e->val.quad.mlhs = node2;
    e->val.quad.mrhs = node3;
    e->val.quad.rhs = node4;
    return e;
}

AST *voidFunction(AST *node1, AST *node2, AST *node3)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_voidFunction;
    e->val.trinary.lhs = node1;
    e->val.trinary.mhs = node2;
    e->val.trinary.rhs = node3;
    return e;
}

AST *functionDefinitionList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_functionDefinitionList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *mainFunction(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_mainFunction;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
    return e;
}

AST *program(AST *node1, AST *node2, AST *node3)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_program;
    e->val.trinary.lhs = node1;
    e->val.trinary.mhs = node2;
    e->val.trinary.rhs = node3;
    return e;
}

AST *typeVoid()
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_typeVoid;
    e->val.binary.lhs = NULL;
    e->val.binary.rhs = NULL;
    return e;
}

AST *def(AST *node1, AST *node2, AST *node3)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_def;
    e->val.trinary.lhs = node1;
    e->val.trinary.mhs = node2;
    e->val.trinary.rhs = node3;
    return e;
}

AST *functionBody(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_functionBody;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

void printAST(AST *e) { 
    if (e == NULL) {
        return;
    }
    switch(e->kind) {
        case k_amp:
            printf("&");
            printAST(e->val.binary.lhs);
            break;
        case k_argList:
            printAST(e->val.binary.lhs);
            printf(",");
            printAST(e->val.binary.rhs);
            break;
        case k_IntLiteral:
            printf("%i", e->val.intLiteral);
            break;
        case k_Identifier:
            printf("%s", e->val.identifier);
            break;
        case k_args: 
            printAST(e->val.binary.lhs);
            printf("(");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_noArgs:
            printAST(e->val.binary.lhs);
            printf("(");
            printf(")");
            break;
        case k_parens: 
            printf("(");
            printAST(e->val.binary.lhs);
            printf(")");
            break;
        case k_positive:
            printf("+");
            printAST(e->val.binary.lhs);
            break;
        case k_negative:
            printf("-");
            printAST(e->val.binary.lhs);
            break;
        case k_multiply:
            printAST(e->val.binary.lhs);
            printf("*");
            printAST(e->val.binary.rhs);
            break;
        case k_divide:
            printAST(e->val.binary.lhs);
            printf("/");
            printAST(e->val.binary.rhs);
            break;
        case k_addition:
            printAST(e->val.binary.lhs);
            printf("+");
            printAST(e->val.binary.rhs);
            break;
        case k_subtraction:
            printAST(e->val.binary.lhs);
            printf("-");
            printAST(e->val.binary.rhs);
            break;
        case k_lessThan: 
            printAST(e->val.binary.lhs);
            printf("<");
            printAST(e->val.binary.rhs);
            break;
        case k_lessThanEqual:
            printAST(e->val.binary.lhs);
            printf("<=");
            printAST(e->val.binary.rhs);
            break;
        case k_greaterThan:
            printAST(e->val.binary.lhs);
            printf(">");
            printAST(e->val.binary.rhs);
            break;
        case k_greaterThanEqual:
            printAST(e->val.binary.lhs);
            printf(">=");
            printAST(e->val.binary.rhs);
            break;
        case k_equal:
            printAST(e->val.binary.lhs);
            printf("==");
            printAST(e->val.binary.rhs);
            break;
        case k_notEqual:
            printAST(e->val.binary.lhs);
            printf("!=");
            printAST(e->val.binary.rhs);
            break;
        case k_assign:
        
        case k_if:
        
        case k_ifElse:
        
        case k_while:
        
        case k_ret:
        
        case k_retExp:

        case k_statementList:
        
        case k_block:
        
        case k_empty:

        default:
            break;
    }
}