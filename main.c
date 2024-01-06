#include <stdio.h>
#include <string.h>
#include "expression.h"

int main()
{
    char a = 'j';
    char val[] = "2 + 3";

    printf("%d", evaluate(val));
    return 0;
}