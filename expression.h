#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

typedef enum Precedence{
    NoPre = 0,
    PreOne,
    PreTwo
} Precedence;

typedef enum Err {
    NoErr = 0,
    DivByZero,
    InvalidFormat,
    MissingOperand,
    MissingOperator
} Err;

typedef struct OperatorNode {
    struct OperatorNode* pNext;
    char key;
} OperatorNode;

typedef struct ValNode {
    struct ValNode* pNext;
    int key;
} ValNode;

typedef struct OperatorList {
    OperatorNode* pTop;
} OperatorList;

typedef struct ValList {
    ValNode* pTop;
} ValList;

OperatorNode* createOperatorNode(char op);

ValNode* createValNode(int val);

void initOpList(OperatorList* list);

void initValList(ValList* list);

int isEmptyOpList(OperatorList* list);

int isEmptyValList(ValList* list);

int pushOpList(OperatorList* list, char op);

int pushValList(ValList* list, int val);

char popOpList(OperatorList* list);

int popValList(ValList* list);

int evaluate(char* expression);

int isValidOp(char op);

int isValidDigit(char op);

void cpyStr(char* des, char* src, int pos, int len);

Err execEpression(ValList* list, char op);

Precedence getPre(char op);

#endif