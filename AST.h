typedef struct EXP EXP;

struct EXP {
    int lineno;
    enum {k_expressionKindIntLiteral, k_expressionKindIdentifier, k_expressionKindAddition, k_expressionKindSubtraction, 
            k_expressionKindMultiplication, k_expressionKindDivision, k_expressionKindLess, k_expressionKindLessEq, k_expressionKindGreater, k_expressionKindGreaterEq} kind;
    union {
        char *identifier;
        int intLiteral;
        struct { EXP *lhs; EXP *rhs; } binary;
    } val;
};

EXP *makeEXP_intLiteral(int intLiteral, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindIntLiteral;
    e->val.intLiteral = intLiteral;
    return e;
}

EXP *makeEXP_identifier(char* identifier, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindIdentifier;
    e->val.identifier = (char *) malloc(strlen(identifier) + 1);
    strcpy(e->val.identifier, identifier);
    return e;
}

EXP *makeEXP_addition(EXP *exp1, EXP *exp2, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindAddition;
    e->val.binary.lhs = exp1;
    e->val.binary.rhs = exp2;
    return e;
}

EXP *makeEXP_subtraction(EXP *exp1, EXP *exp2, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindSubtraction;
    e->val.binary.lhs = exp1;
    e->val.binary.rhs = exp2;
    return e;
}

EXP *makeEXP_multiplication(EXP *exp1, EXP *exp2, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindMultiplication;
    e->val.binary.lhs = exp1;
    e->val.binary.rhs = exp2;
    return e;
}

EXP *makeEXP_division(EXP *exp1, EXP *exp2, int lineno)
{
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindDivision;
    e->val.binary.lhs = exp1;
    e->val.binary.rhs = exp2;
    return e;
}

void prettyEXP(EXP *e) 
{
    switch(e->kind) {
        case k_expressionKindIntLiteral:
            printf("%i", e->val.intLiteral);
            break;
        case k_expressionKindIdentifier:
            break;
        case k_expressionKindAddition:
            printf("(");
            prettyEXP(e->val.binary.lhs);
            printf("+");
            prettyEXP(e->val.binary.rhs);
            printf(")");
            break;
        case k_expressionKindSubtraction:
            printf("(");
            prettyEXP(e->val.binary.lhs);
            printf("-");
            prettyEXP(e->val.binary.rhs);
            printf(")");
            break;
        case k_expressionKindMultiplication:
            printf("(");
            prettyEXP(e->val.binary.lhs);
            printf("*");
            prettyEXP(e->val.binary.rhs);
            printf(")");
            break;
        case k_expressionKindDivision:
            printf("(");
            prettyEXP(e->val.binary.lhs);
            printf("/");
            prettyEXP(e->val.binary.rhs);
            printf(")");
            break;
        default:
            break;  
    }
}