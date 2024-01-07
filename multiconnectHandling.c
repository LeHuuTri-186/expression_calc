#include "multiconnectHandling.h"
#define MAX 1000

void* handleEval(void* desc)
{
    int sock = *((int*)desc);
    char ch[MAX];
    int res;
    int readSize;
    Err error;
    readSize = read( sock, ch, MAX);

    printf("Connection establised!: Sock %d\n");


    if (readSize <= 0)
    {
        printf("ERROR\n");
    }
    
    ch[strlen(ch) - 1] = '\0';

	printf("%lu\n", strlen(ch));
	printf("%s\n", ch);

	res = evaluate(ch, &error);

	printf("%d\n", res);
		/* Gửi trả dữ liệu về cho trình khách */

    write(sock, &error, sizeof(error));
    switch (error)
    {
    case NoErr:
        write( sock, &res, sizeof(res));
        break;
    case InvalidFormat:
        strcpy(ch, "Invalid format\0");
        write( sock, ch, sizeof(ch));
        break;
    case MissingOperand:
        strcpy(ch, "Missing operand\0");
        write( sock, ch, sizeof(ch));
        break;
    case MissingOperator:
        strcpy(ch, "Missing operator\0");
        write( sock, ch, sizeof(ch));
        break;
    case DivByZero:
        strcpy(ch, "Divide by zero\0");
        write( sock, ch, sizeof(ch));
        break;
    }

    free(desc);
    desc = NULL;

    printf("Closing connection\n");

    return NULL;
}