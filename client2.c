// 単純なTCPクライアント
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <arpa/inet.h>
#include <netdb.h>	// for hostent

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
	
	struct hostent *host;
	host = gethostbyname("localhost");
	//host = gethostbyname("ubuntu.server1");
	if(host == NULL){
		return 1;
	}
	// 32bit値に変換する（重要）
	server.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];

	printf("%s:%s\n", (char *)host->h_name, inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));

	/*
	// サーバに接続
	connect(sock, (struct sockaddr *)&server, sizeof(server));

	// データ受信
	n = read(sock, buf, sizeof(buf));
	printf("%d, %s\n", n, buf);
	*/
	// 終了
	close(sock);

	return 0;
}