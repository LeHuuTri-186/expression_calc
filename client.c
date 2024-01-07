/* 1. Tạo các #include cần thiết để gọi hàm socket */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/* dành riêng cho AF_INET */
#include <netinet/in.h>
#include <arpa/inet.h>
#include "expression.h"
#define MAX 1000

int main()
{
	int sockfd; /* số mô tả socket – socket handle */
	int len;
	struct sockaddr_in address; /* structure sockaddr_in, chứa các thông tin về socket AF_INET */
	int result;
	char ch[MAX];
	int res;
	Err error;
	
	/* 2. Tạo socket cho trình khách. Lưu lại số mô tả socket */
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	
	/* 3. Đặt tên và gán địa chỉ kết nối cho socket theo giao thức Internet */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	address.sin_port = htons( 9734 );
	len = sizeof( address );
	
	/* 4. Thực hiện kết nối */
	result = connect( sockfd, (struct sockaddr*)&address, len );
	if ( result == -1 ) {
		perror( "Oops: client1 problem" );
		return 1;
	}
	
	printf("Input your equation here: ");
	fgets(ch, MAX, stdin);
	/* 5. Sau khi socket kết nối, chúng ta có thể đọc ghi dữ liệu của socket tương tự đọc ghi trên file */
	write( sockfd, ch, sizeof(ch));
	read ( sockfd, &error, sizeof(error));

	if (error == NoErr)
	{
		read ( sockfd, &res, sizeof(res));
		printf( "res from server: %d\n", res );
		close( sockfd );

		return 0;
	}
	
	int n = read ( sockfd, ch, sizeof(ch));
	ch[n] = '\0';

	printf( "res from server: %s\n", ch );
	
	return 0;
}