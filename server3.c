// 繰り返し接続可能なTCPサーバ(エラー処理追加)
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
	int n;

	// ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 < 0){
		perror("socket");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0){
		perror("bind");
		return 1;
	}

	// 接続待機
	if(listen(sock0, 5) != 0){
		perror("listen");
		return 1;
	}

	while(1){
		// クライアントの要求受付
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0){
			perror("accept");
			return 1;
		}

		// クライアントへの送信
		n = write(sock, "HELLO", 5);
		if(n < 1){
			perror("write");
			close(sock);
			break;
		}

		// TCPセッションの終了
		close(sock);
	}

	// サーバ終了
	close(sock0);

	return 0;
}