#ifndef _MULTICONNECTHANDLING_H_
#define _MULTICONNECTHANDLING_H_

#include "expression.h"
/* 1.Tạo các #include cần thiết */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/* dành riêng cho AF_INET */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "expression.h"
#include "string.h"
#include "multiconnectHandling.h"
#include "stdlib.h"

void* handleEval(void* desc);

#endif