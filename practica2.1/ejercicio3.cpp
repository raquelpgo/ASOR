#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main() {

  //Vemos que en realidad 0 no es un error porque es success y que a partir del 133 son unknown
   for (int i=0; i<=255; i++)
   {
   	cout << strerror(i) << endl;
   }
   
   return 0;
}
