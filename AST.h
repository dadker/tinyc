typedef struct AST AST;

struct AST {
    int lineno;
    enum {k_IntLiteral, k_Identifier, k_Addition} kind;
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