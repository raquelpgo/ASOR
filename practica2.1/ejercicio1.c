#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
   printf("%s\n", strerror(setuid(0)));
   return 1;
}

