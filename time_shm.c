#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(char argc, char *argv[]) {

  if (argc <= 1) {
    fprintf ( stderr, "INVALID ARGUMENTS: Use \"filename [arguments]\"\n", argv[0] );
    return 1;
  }

  /*name of shared mem object*/
  const char *name = "ElapsedTime:";

  /*shared memory file descriptor*/
  int smfd;

  /*pointer to the shared memory object */
  struct timeval startTime, endTime, elapsedTime, *ptr, s;

  /*the size in buytes of shared mem object */
  int size;
  size = sizeof(startTime);

  /*create new process id*/
  pid_t pid;

  /* fork a child process */
  pid = fork();

  if (pid < 0) {
    fprintf (stderr, "Fork Failed");
    return 1;
  }

  else if (pid == 0) {
    /*create the shared mem obect*/
    smfd = shm_open(name, O_CREAT | O_RDWR, 0666);
    //smfd = shmget(1009, sizeof(startTime), 0666 | IPC_CREAT);

    /* config size of shared mem obj */
    ftruncate(smfd,size);

    /*mem map the shared mem object*/
    ptr = (struct timeval *)
      mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, smfd, 0);

      // Get current time
      gettimeofday( &startTime, NULL );

      /*write to shared mem obj */
      memcpy(ptr, &startTime, sizeof(startTime));
      //printf("\nBegin: %ld.%06ld seconds\n", startTime.tv_sec,startTime.tv_usec );

      /* Execute Command */
      execlp(argv[1], " " ,argv[2],NULL);
  }
  else { 
    wait(NULL);

    // get the end time
    gettimeofday( &endTime, NULL );

    /* shared memory object */
    smfd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /*memory map */
    ptr = (struct timeval *)
      mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, smfd, 0);

    s = *ptr;

    /* test print functions */
    //printf("%ld.%6ld\n",startTime.tv_sec);
    //printf("\nEnd: %ld.%06ld seconds\n", endTime.tv_sec,endTime.tv_usec );
    //printf("\nEnd: %ld.%06ld seconds\n", s.tv_sec,s.tv_usec );

    /* calculate elapsed time */
    timersub( &endTime, &s, &elapsedTime);

    printf("\nElapsed time: %ld microseconds\n", (elapsedTime.tv_sec,
    elapsedTime.tv_usec) );

    shm_unlink(name);
  }
  return 0;
}
