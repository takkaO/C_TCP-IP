// 繰り返し接続可能なTCPサーバ
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close

int main(){
	int sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int sock;

	// ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

	// 接続待機
	listen(sock0, 5);

	while(1){
		// クライアントの要求受付
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);

		// クライアントへの送信
		write(sock, "HELLO", 5);

		// TCPセッションの終了
		close(sock);
	}

	// サーバ終了
	close(sock0);

	return 0;
}