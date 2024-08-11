/*
	- 仕様
	echoを1行だけ受け取るコードにする。
	クライアントは標準入力のまま。
	サーバ側のmainループでselectする。

	問題の書き方が悪い。意図が読み取りづらい

*/


/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    listenfd = Open_listenfd(argv[1]);  //line:conc:select:openlistenfd

    FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
    FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd

    while (1) {
	ready_set = read_set;
	Select(listenfd+1, &ready_set, NULL, NULL, NULL); //line:conc:select:select
	if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
	    command(); /* Read command line from stdin */
	if (FD_ISSET(listenfd, &ready_set)) { //line:conc:select:listenfdready
            clientlen = sizeof(struct sockaddr_storage); 
	    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	    echo(connfd); /* Echo client input until EOF */
	    Close(connfd); 
	}
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
	exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */


void echo(int connfd) {
  ssize_t n;
  char buf[1];

  while ((n = Rio_readn(connfd, buf, 1)) > 0) {
    Rio_writen(connfd, buf, n);
    if (buf[0] = '\n')
      break;
  }
//   return -1;/
}


// answer

// #include "csapp.h"

// /* read line from connfd and echo line to connfd */
// int echo_line(int connfd);

// void command(void);

// int main(int argc, char **argv)
// {
//   int listenfd, connfd;
//   socklen_t clientlen;
//   struct sockaddr_storage clientaddr;
//   fd_set read_set, ready_set;

//   if (argc != 2) {
//     fprintf(stderr, "usage: %s <port>\nuse port 5000 here\n", argv[0]);
//     // default port 5000
//     listenfd = Open_listenfd("5000");
//   } else {
//     listenfd = Open_listenfd(argv[1]);  //line:conc:select:openlistenfd
//   }

//   FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
//   FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
//   FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd

//   // max n for select
//   int n = listenfd+1;

//   while (1) {
//     ready_set = read_set;
//     Select(n, &ready_set, NULL, NULL, NULL); //line:conc:select:select

//     if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
//       command(); /* Read command line from stdin */

//     if (FD_ISSET(listenfd, &ready_set)) { //line:conc:select:listenfdready
//       clientlen = sizeof(struct sockaddr_storage);
//       connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);


//       // listen to accepted io ports
//       if (connfd+1 > FD_SETSIZE) {
//         fprintf(stderr, "too many clients\n");
//         Close(connfd);
//       }
//       n = n > connfd+1 ? n : connfd+1;
//       FD_SET(connfd, &read_set);
//     }

//     // echo one line every time
//     int fd;
//     for (fd = listenfd+1; fd < n; fd++)
//       if (FD_ISSET(fd, &ready_set))
//         if (echo_line(fd) == -1) {
//           Close(fd);
//           FD_CLR(fd, &read_set);
//         }
//   }
// }

// void command(void) {
//   char buf[MAXLINE];
//   if (!Fgets(buf, MAXLINE, stdin))
//     exit(0); /* EOF */
//   printf("%s", buf); /* Process the input command */
// }

// int echo_line(int connfd) {
//   ssize_t n;
//   char buf[1];

//   while ((n = Rio_readn(connfd, buf, 1)) > 0) {
//     Rio_writen(connfd, buf, n);
//     if (buf[0] = '\n')
//       return 0;
//   }
//   return -1;
// }

