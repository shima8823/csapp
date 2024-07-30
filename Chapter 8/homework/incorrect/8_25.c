// 良問

#include "csapp.h"


// void handler1(int sig) 
// {
//     int olderrno = errno;

// 	if ((waitpid(-1, NULL, 0)) < 0)
// 		sio_error("waitpid error");
// 	Sio_puts("Handler reaped child\n");
	
// 	errno = olderrno;
// }

// char *tfgets(char * restrict str, int size, FILE * restrict stream) {
// 	if (signal(SIGCHLD, handler1) == SIG_ERR)
// 		unix_error("signal error");
// 	if (Fork() == 0) {
// 		sleep(5);
		
// 		return NULL;
// 	}

// 	return fgets(str, size, stream);
// }

sigjmp_buf buf;

void handler(int sig) {
  /* jump */
  siglongjmp(buf, 1);
}

char* tfgets(char* s, int size, FILE* stream) {
  char* result;

  if (!sigsetjmp(buf, 1)) {
    alarm(5);
    if (signal(SIGALRM, handler) == SIG_ERR)
      unix_error("set alarm handler error");
    return fgets(s, size, stream);
  } else {
    /* run out of time */
    return NULL;
  }
}

int main() {
    char buffer[100];

    printf("Enter a string: ");
    // if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (tfgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}