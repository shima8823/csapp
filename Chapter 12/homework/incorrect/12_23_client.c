#include "csapp.h"

int main(int argc, char **argv)
{
  int clientfd;
  char *host, *port;
  char *buf = "something to send\n";
  rio_t rio;

  host = "127.0.0.1";
  port = "1234";

  clientfd = Open_clientfd(host, port);

  Rio_readinitb(&rio, clientfd);
  Rio_writen(clientfd, buf, strlen(buf));
//   Close(clientfd);
  exit(0);
}