typedef struct AST AST;

struct AST {
    int lineno;
    enum {k_IntLiteral, k_Identifier, k_Addition, k_Subtraction, k_lessThan, k_lessThanEqual, k_greaterThan, k_greaterThanEqual, k_equal, k_notEqual, k_return, k_assign} kind;
    union {
        char *identifier;
        int intLiteral;
        struct { AST *lhs; AST *rhs; } binary;
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