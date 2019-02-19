// 単純なTCPクライアント
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <arpa/inet.h>

int main()
{
	int sock;
	struct sockaddr_in server;
	char buf[32] = {0};
	int n;

	// ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// 接続先の設定
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// サーバに接続
	connect(sock, (struct sockaddr *)&server, sizeof(server));

	// データ受信
	n = read(sock, buf, sizeof(buf));
	printf("%d, %s\n", n, buf);

	// 終了
	close(sock);

	return 0;
}