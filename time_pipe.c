#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

int main(char argc, char *argv[]) {

  if (argc <= 1) {
    fprintf ( stderr, "INVALID ARGUMENTS: Use \"filename [arguments]\"\n", argv[0] );
    return 1;
  }

  int fd[2];
  pid_t pid;

  /* create the pipe */
  if (pipe(fd) == -1) {
     fprintf(stderr,"Pipe failed");
     return 1;
  }
  /* fork a child process */
  pid = fork();

  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  if (pid > 0) { /* parent process */

      struct timeval receiveStart, endTime, et;

      /* close the unused end of the pipe */
      close(fd[WRITE_END]);

      /* read from the pipe */
      read(fd[READ_END], &receiveStart, sizeof(receiveStart));

      //get current time of day
      gettimeofday( &endTime, NULL );

      // calculate elapsed time
      timersub( &endTime, &receiveStart, &et );

      printf( "\nElapsed time: %ld.%06ld microseconds\n", et.tv_sec, et.tv_usec );

      /* close the read end of the pipe */
      close(fd[READ_END]);
  } else {
    struct timeval startTime;
    /* child process */
    /* close the unused end of the pipe */
    close(fd[READ_END]);
    // Get current time
    gettimeofday( &startTime, NULL );
    /* write to the pipe */
    write(fd[WRITE_END], &startTime, sizeof(startTime));
    /* close the write end of the pipe */
    close(fd[WRITE_END]);
    execlp(argv[1], " " ,argv[2],NULL);
  }

  return 0;
}
