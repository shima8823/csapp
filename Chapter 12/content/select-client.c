#include "csapp.h"

int main(int argc, char **argv) {
    int clientfd;
    char *host, *port;
    char buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    // 標準入力から1行読み込んで送信
    if (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        // サーバーからの応答を表示
        if (Rio_readlineb(&rio, buf, MAXLINE) > 0) {
            Fputs(buf, stdout);
        }
    }
    Close(clientfd);
    return 0;
}