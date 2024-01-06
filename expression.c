#include "expression.h"
#include <stdlib.h>
#include <string.h>

OperatorNode* createOperatorNode(char op)
{
    OperatorNode* pNode = (OperatorNode*)malloc(sizeof(OperatorNode));

    if (pNode)
    {
        pNode->key = op;
        pNode->pNext = NULL;
    }

    return pNode;
}

ValNode* createValNode(int val)
{
    ValNode* pNode = (ValNode*)malloc(sizeof(ValNode));

    if (pNode)
    {
        pNode->key = val;
        pNode->pNext = NULL;
    }

    return pNode;
}

void initOpList(OperatorList* list)
{
    if (list->pTop)
    {
        return;
    }

    list->pTop = NULL;
}

void initValList(ValList* list)
{
    if (list->pTop)
    {
        return;
    }

    list->pTop = NULL;
}

int isEmptyOpList(OperatorList* list)
{
    return list->pTop;
}

int isEmptyValList(ValList* list)
{
    return list->pTop;
}

int pushOpList(OperatorList* list, char op)
{
    int res = -1;

    if (isEmptyOpList(list))
    {
        list->pTop = createOperatorNode(op);
        res = 1;

        return res;
    }

    OperatorNode* pNode = createOperatorNode(op);

    pNode->pNext = list->pTop;
    list->pTop = pNode;

    res = 1;

    return res;
}

int pushValList(ValList* list, int val)
{
    int res = -1;

    if (isEmptyValList(list))
    {
        list->pTop = createValNode(val);
        res = 1;

        return res;
    }

    ValNode* pNode = createValNode(val);

    pNode->pNext = list->pTop;
    list->pTop = pNode;

    res = 1;

    return res;
}

char popOpList(OperatorList* list)
{
    if (isEmptyOpList(list))
    {
        return '?';
    }

    char res = list->pTop->key;

    OperatorNode* pNode = list->pTop;
    list->pTop = pNode->pNext;

    free(pNode);
    pNode = NULL;

    return res;
}

int popValList(ValList* list)
{
    if (isEmptyValList(list))
    {
        return INT32_MIN;
    }

    int res = list->pTop->key;

    ValNode* pNode = list->pTop;
    list->pTop = pNode->pNext;

    free(pNode);
    pNode = NULL;

    return res;
}

int evaluate(char* expression)
{
    OperatorList opList;
    ValList valList;
    
    initOpList(&opList);
    initValList(&valList);

    int len = strlen(expression);

    for (int i = 0; i < len; ++i)
    {
        if (expression[i] == ' ')
        {
            continue;
        }

        if (!isValidOp(expression[i]) && !isValidDigit(expression[i]))
        {
            return INT32_MIN;
        }

        if (expression[i] == '(')
        {
            pushOpList(&opList, expression[i]);

            continue;
        }

        if (expression[i] == '-' && i != len)
        {
            int count = 0;

            while (isValidDigit(expression[i + 1 + count]))
            {
                count++;
            }

            if (!count)
            {
                pushOpList(&opList, expression[i]);

                continue;
            }

            char* val = (char*)malloc(count + 2);

            cpyStr(val, expression, i, count + 1);

            pushValList(&valList, atoi(val));

            continue;
        }

        if (expression[i] == ')')
        {
            while (1)
            {
                if (isEmptyOpList(&opList))
                {
                    return INT32_MIN;
                }

                char op = popOpList(&opList);

                if (op == '(')
                {
                    break;
                }

                Err error = execEpression(&valList, op);

                if (error)
                {
                    return INT32_MIN;
                }
            }

            continue;
        }

        Precedence pre = getPre(expression[i]);

        while (1)
        {
            if (isEmptyOpList(&opList))
            {
                break;
            }

            if (pre > getPre(opList.pTop->key))
            {
                break;
            }

            char op = popOpList(&opList);

            Err error = execEpression(&valList, op);

            if (error)
            {
                return INT32_MIN;
            }
        }

        pushOpList(&opList, expression[i]);
    }

    while (1)
    {
        if (isEmptyOpList(&opList))
        {
            break;
        }

        char op = popOpList(&opList);

        Err error = execEpression(&valList, op);

        if (error)
        {
            return INT32_MIN;
        }
    }

    int result = popValList(&valList);

    if (!isEmptyValList(&valList))
    {
        return INT32_MIN;
    }

    return result;
}

int isValidOp(char op)
{
    int res = 1;

    switch (op)
    {
    case '+': case '-': case '*': case '/':
        break;
    default:
        res = 0;
        break;
    }

    return res;
}

int isValidDigit(char op)
{
        int res = 1;

    switch (op)
    {
    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    case '8': case '9':
        break;
    default:
        res = 0;
        break;
    }

    return res;
}

void cpyStr(char* des, char* src, int pos, int len)
{
    for (int i = 0; i < len; i++)
    {
        des[i] = src[pos + i];
    }

    des[len] = '\0';
}

Err execEpression(ValList* list, char op)
{
    Err error = NoErr;
    if (isEmptyValList(list))
    {
        error = MissingOperand;

        return error;
    }

    int b = popValList(list);

    if (isEmptyValList(list))
    {
        error = MissingOperand;

        return error;
    }

    int a = popValList(list);

    if (!b && op == '/')
    {
        error = DivByZero;

        return error;
    }

    switch (op)
    {
    case '+':
        pushValList(list, a + b);
        break;
    case '-':
        pushValList(list, a - b);
        break;
    case '*':
        pushValList(list, a * b);
        break;
    case '/':
        pushValList(list, a / b);
    break;
    }

    return error;
}

Precedence getPre(char op)
{
    Precedence pre = NoPre;

    switch (op)
    {
    case '+': case '-':
        pre = PreOne;
        break;
    case '*': case '/':
        pre = PreTwo;
        break;
    }

    return pre;
}