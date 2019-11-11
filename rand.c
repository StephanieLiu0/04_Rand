#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int randNum() {
  int fileDes = open ("/dev/random", O_RDONLY);
  if (fileDes < 0) {
    printf("Open errno %d: %s\n", errno, strerror(errno));
  }
  int buff[1];
  if (read (fileDes, buff, sizeof(int)) < 0) {
    printf("Read errno %d: %s\n", errno, strerror(errno));
  }
  return *buff;
}

int main() {

  // populate array
  int ARR_SIZE = 10;
  int array[ARR_SIZE];
  for (int i = 0; i < ARR_SIZE; i++) {
   int num = randNum();
   array[i] = num;
   printf("index %d: %d\n", i, num);
  }

  // write to file
  int fileDes = open ("rand.txt", O_CREAT|O_WRONLY, 0755);
  if (fileDes < 0) {
    printf("Open errno %d: %s\n", errno, strerror(errno));
    return -1;
  }
  if (write (fileDes, array, sizeof(int) * ARR_SIZE) < 0) {
    printf("Write errno %d: %s\n", errno, strerror(errno));
    return -1;
  }

  // read from file
  int newArray[ARR_SIZE];
  fileDes = open ("rand.txt", O_RDONLY);
  if (fileDes < 0) {
    printf("Open errno %d: %s\n", errno, strerror(errno));
    return -1;
  }
  if (read (fileDes, newArray, sizeof(int) * ARR_SIZE) < 0) {
    printf("Read errno %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fileDes);

  // verify new array
  printf("\nVerification\n");
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("index %d: %d\n", i, newArray[i]);
  }

  return 0;
}
