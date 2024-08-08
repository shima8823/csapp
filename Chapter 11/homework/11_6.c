/*

GET /11_6.c HTTP/1.0
POST /11_6.c HTTP/1.0

A.
Rio_writen(fd, buf, strlen(buf)); // A

B.
read_requesthdrs

C.
HTTP/1.1

D.
Host: localhost:1234
Connection: keep-alive
Cache-Control: max-age=0
sec-ch-ua: "Not)A;Brand";v="99", "Google Chrome";v="127", "Chromium";v="127"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*X/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: cross-site
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br, zstd
Accept-Language: en-GB,en;q=0.9,ja-JP;q=0.8,ja;q=0.7,en-US;q=0.6

Connection: 送信者が特定のコネクションに必要なオプションを指定できる
Cache-Control: リクエスト/レスポンス の連鎖に沿ったすべてのキャッシュ機構が従わなければならない。ディレクティブ を指定するために使用される。 ディレクティブは、キャッシュがリクエストやレスポンスに 悪影響を与えないようにするための動作を指定します。
User-Agent: クエストを発信した ユーザーエージェントに関する情報を含む。 これは、統計的な目的、プロトコル違反のトレース、特定のユーザー エージェントの制限を避けるために応答を調整するためのユーザーエージェントの 自動認識のためである
Accept: 応答で受け入れられる特定の メディアタイプを指定するために使用できる。 Acceptヘッダは、インライン画像に対するリクエストの場合のように、 リクエストが望ましい型の小さなセットに特に限定されていることを 示すために使うことができる。
Accept-Encoding: Acceptに似ているが、 応答で受け入れられるcontent-coding(セクション3.5)を制限する。
Accept-Language: Acceptに似ているが、リクエス トに対する応答として望ましい自然言語のセットを制限する。

- 定義されていない
sec-ch-
Upgrade-Insecure-Requests
Sec-Fetch-

*/


/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *	 GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh 
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);

int main(int argc, char **argv) 
{
	int listenfd, connfd;
	char hostname[MAXLINE], port[MAXLINE];
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;

	/* Check command line args */
	if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
	}

	listenfd = Open_listenfd(argv[1]);
	while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
		Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
					port, MAXLINE, 0);
		printf("Accepted connection from (%s, %s)\n", hostname, port);
	doit(connfd);											 //line:netp:tiny:doit
	Close(connfd);											//line:netp:tiny:close
	}
}
/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void doit(int fd) 
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];
	rio_t rio;

	/* Read request line and headers */
	Rio_readinitb(&rio, fd);
	if (!Rio_readlineb(&rio, buf, MAXLINE))  //line:netp:doit:readrequest
		return;
	printf("%s", buf);
	sscanf(buf, "%s %s %s", method, uri, version);	   //line:netp:doit:parserequest
	if (strcasecmp(method, "GET")) {					 //line:netp:doit:beginrequesterr
		clienterror(fd, method, "501", "Not Implemented",
					"Tiny does not implement this method");
		return;
	}													//line:netp:doit:endrequesterr
	read_requesthdrs(&rio);							  //line:netp:doit:readrequesthdrs

	// Rio_writen(fd, buf, strlen(buf)); // A

	/* Parse URI from GET request */
	is_static = parse_uri(uri, filename, cgiargs);	   //line:netp:doit:staticcheck
	if (stat(filename, &sbuf) < 0) {					 //line:netp:doit:beginnotfound
	clienterror(fd, filename, "404", "Not found",
			"Tiny couldn't find this file");
	return;
	}													//line:netp:doit:endnotfound

	if (is_static) { /* Serve static content */		  
	if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) { //line:netp:doit:readable
		clienterror(fd, filename, "403", "Forbidden",
			"Tiny couldn't read the file");
		return;
	}
		serve_static(fd, filename, sbuf.st_size);		//line:netp:doit:servestatic
	}
	else { /* Serve dynamic content */
	if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) { //line:netp:doit:executable
		clienterror(fd, filename, "403", "Forbidden",
			"Tiny couldn't run the CGI program");
		return;
	}
	serve_dynamic(fd, filename, cgiargs);			//line:netp:doit:servedynamic
	}
}
/* $end doit */

/*
 * read_requesthdrs - read HTTP request headers
 */
/* $begin read_requesthdrs */
void read_requesthdrs(rio_t *rp) 
{
	char buf[MAXLINE];

	// B
	umask(S_IWGRP | S_IWOTH);
	int fd = Open("log.txt", O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd < 0)
		unix_error("Open Error");

	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
	dprintf(fd, "%s", buf);
	while(strcmp(buf, "\r\n")) {		  //line:netp:readhdrs:checkterm
	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
	dprintf(fd, "%s", buf);
	}
	
	Close(fd);

	return;
}
/* $end read_requesthdrs */

/*
 * parse_uri - parse URI into filename and CGI args
 *			 return 0 if dynamic content, 1 if static
 */
/* $begin parse_uri */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
	char *ptr;

	if (!strstr(uri, "cgi-bin")) {  /* Static content */ //line:netp:parseuri:isstatic
	strcpy(cgiargs, "");							 //line:netp:parseuri:clearcgi
	strcpy(filename, ".");						   //line:netp:parseuri:beginconvert1
	strcat(filename, uri);						   //line:netp:parseuri:endconvert1
	if (uri[strlen(uri)-1] == '/')				   //line:netp:parseuri:slashcheck
		strcat(filename, "home.html");			   //line:netp:parseuri:appenddefault
	return 1;
	}
	else {  /* Dynamic content */						//line:netp:parseuri:isdynamic
	ptr = index(uri, '?');						   //line:netp:parseuri:beginextract
	if (ptr) {
		strcpy(cgiargs, ptr+1);
		*ptr = '\0';
	}
	else 
		strcpy(cgiargs, "");						 //line:netp:parseuri:endextract
	strcpy(filename, ".");						   //line:netp:parseuri:beginconvert2
	strcat(filename, uri);						   //line:netp:parseuri:endconvert2
	return 0;
	}
}
/* $end parse_uri */

/*
 * serve_static - copy a file back to the client 
 */
/* $begin serve_static */
void serve_static(int fd, char *filename, int filesize)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXBUF];

	/* Send response headers to client */
	get_filetype(filename, filetype);	//line:netp:servestatic:getfiletype
	sprintf(buf, "HTTP/1.0 200 OK\r\n"); //line:netp:servestatic:beginserve
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n", filesize);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
	Rio_writen(fd, buf, strlen(buf));	//line:netp:servestatic:endserve

	/* Send response body to client */
	srcfd = Open(filename, O_RDONLY, 0); //line:netp:servestatic:open
	srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0); //line:netp:servestatic:mmap
	Close(srcfd);					   //line:netp:servestatic:close
	Rio_writen(fd, srcp, filesize);	 //line:netp:servestatic:write
	Munmap(srcp, filesize);			 //line:netp:servestatic:munmap
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
	if (strstr(filename, ".html"))
	strcpy(filetype, "text/html");
	else if (strstr(filename, ".gif"))
	strcpy(filetype, "image/gif");
	else if (strstr(filename, ".png"))
	strcpy(filetype, "image/png");
	else if (strstr(filename, ".jpg"))
	strcpy(filetype, "image/jpeg");
	else
	strcpy(filetype, "text/plain");
}  
/* $end serve_static */

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
/* $begin serve_dynamic */
void serve_dynamic(int fd, char *filename, char *cgiargs) 
{
	char buf[MAXLINE], *emptylist[] = { NULL };

	/* Return first part of HTTP response */
	sprintf(buf, "HTTP/1.0 200 OK\r\n"); 
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	Rio_writen(fd, buf, strlen(buf));
  
	if (Fork() == 0) { /* Child */ //line:netp:servedynamic:fork
	/* Real server would set all CGI vars here */
	setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
	Dup2(fd, STDOUT_FILENO);		 /* Redirect stdout to client */ //line:netp:servedynamic:dup2
	Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
	}
	Wait(NULL); /* Parent waits for and reaps child */ //line:netp:servedynamic:wait
}
/* $end serve_dynamic */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
	char buf[MAXLINE];

	/* Print the HTTP response headers */
	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n\r\n");
	Rio_writen(fd, buf, strlen(buf));

	/* Print the HTTP response body */
	sprintf(buf, "<html><title>Tiny Error</title>");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "<body bgcolor=""ffffff"">\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
	Rio_writen(fd, buf, strlen(buf));
}
/* $end clienterror */