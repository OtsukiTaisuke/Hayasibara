#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
void recv_thread(void); // 受信用スレッド
int sock;
int main(int argc, char *argv[]){
	pthread_t t1;

	struct sockaddr_in addr;
	char send_buf[2048];
	sock = socket(AF_INET, SOCK_DGRAM, 0); // UDP/IP ソケットの作成
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1])); // 受信ポートの設定
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	pthread_create(&t1, NULL, (void *)recv_thread, (void *)NULL); // 受信用スレッド開始
	addr.sin_port = htons(atoi(argv[2])); // 送信ポートの設定
	if (argc == 4) addr.sin_addr.s_addr = inet_addr(argv[3]); // IP アドレスの設定
	while(1){
		scanf("%s",send_buf);
		if (!strcmp(send_buf,"quit")) break; // quit と入力すると終了
		sendto(sock, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr, sizeof(addr));
	}
	close(sock);
	return 0;
}
// recv はブロック（入力があるまでウェイト）で，別スレッドにしないとキーボード入力が行えない
void recv_thread(void){
	char recv_buf[2048];
	while(1){
		int num = recv(sock, recv_buf, sizeof(recv_buf), 0); // 受信するまで停止
		recv_buf[num] = 0; // 文字列の終点に 0 を挿入
		printf("%s\n", recv_buf);
	}
}
