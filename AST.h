typedef struct AST AST;

struct AST {
    enum {k_IntLiteral, k_Identifier, k_Addition, k_Subtraction, k_multiply, k_divide,  k_lessThan, k_lessThanEqual, k_greaterThan, k_greaterThanEqual, k_equal, k_notEqual, k_return, k_assign,
            k_if, k_ifElse, k_while, k_statementList, k_program} kind;
    union {
        char *identifier;
        int intLiteral;
        struct { AST *lhs; AST *rhs; } binary;
        struct { AST *node1; AST *node2; AST *node3; } trinary;
    } val;
};

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

AST *addition(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_Addition;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *subtraction(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_Subtraction;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
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

AST *ret(AST *node1)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_return;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = NULL;
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
    e->val.trinary.node1 = node1;
    e->val.trinary.node2 = node2;
    e->val.trinary.node3 = node3;
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

AST *statementList(AST *node1, AST *node2)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_statementList;
    e->val.binary.lhs = node1;
    e->val.binary.rhs = node2;
    return e;
}

AST *program(AST *node1, AST *node2, AST *node3)
{
    AST *e = malloc(sizeof(AST));
    e->kind = k_program;
    e->val.trinary.node1 = node1;
    e->val.trinary.node2 = node2;
    e->val.trinary.node3 = node3;
    return e;
}

void printAST(AST *e) {
    switch(e->kind) {
        case k_IntLiteral:
            printf("%i", e->val.intLiteral);
            break;
        case k_Identifier:
            printf("%s", e->val.identifier);
            break;
        case k_Addition:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("+");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_Subtraction:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("-");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_multiply:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("*");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_divide:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("/");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_lessThan:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("<");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_lessThanEqual:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("<=");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_greaterThan:
            printf("(");
            printAST(e->val.binary.lhs);
            printf(">");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_greaterThanEqual:
            printf("(");
            printAST(e->val.binary.lhs);
            printf(">=");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_equal:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("==");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_notEqual:
            printf("(");
            printAST(e->val.binary.lhs);
            printf("!=");
            printAST(e->val.binary.rhs);
            printf(")");
            break;
        case k_return:
            printf("(");
            printAST(e->val.binary.lhs);
            printf(";");
            break;
        case k_assign:
            printAST(e->val.binary.lhs);
            printf("=");
            printAST(e->val.binary.rhs);
            printf(";");
            break;
        case k_if:
            printf("IF (");
            printAST(e->val.binary.lhs);
            printf(")");
            printAST(e->val.binary.rhs);
            break;
        case k_ifElse:
            printf("IF (");
            printAST(e->val.trinary.node1);
            printf(")");
            printAST(e->val.trinary.node2);
            printf("ELSE");
            printAST(e->val.trinary.node3);
            break;
        case k_while:

            break;
        case k_statementList:

            break;
        case k_program:

            break;
        default:

            break;
    }
}