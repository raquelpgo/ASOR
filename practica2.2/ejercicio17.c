#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char **argv) {


	if (argc < 2) 
	{
		 printf("Especifique la ruta del fichero!\n");
		 return -1;
	}

	DIR *dir = opendir(argv[1]);

	if (dir == NULL )
	{
		printf("No existe el directorio!\n");
		return -1;
	}

	struct dirent *act;
	struct stat info;
	size_t spath = strlen(argv[1]);
	act = readdir(dir);
	long int total = 0;

	while (act != NULL) 
	{
    		char *path = malloc(sizeof(char)*(spath + strlen(act->d_name) + 3));
		strcpy(path, argv[1]);
    		strcat(path, "/");
    		strcat(path, act->d_name);

		if (stat(path, &info) == -1) 
		{
      			printf("Ha habido un problema al leer el archivo!\n");
      			free(path);
      			closedir(dir);
      			return -1;
    		} 
	
		else 
		{
      			if (S_ISREG(info.st_mode))
			{
				bool ex = false;
				int i = 0, x = info.st_mode;
				printf("%d ",x);
				while(!ex && i < 3)
				{
					

					if ((x % 10) % 2 != 0)
					{
						ex = true;
					}

					x /= 10;
					i++;
				}
				//EL PROBLEMA DA CON LOS ARCHIVOS CREADOS CON ROOT QUE SIEMPRE SALEN EJECUTABLES
				
        			printf("%s", act->d_name);
				if (ex)
				{
					printf(" *");				
				}
				printf("\n");
        			total +=  (info.st_blksize/8)*info.st_blocks;

      			}
	 
			else if (S_ISDIR(info.st_mode)) 
			{
        			printf("%s/ \n", act->d_name);

			} 

			else if (S_ISLNK(info.st_mode)) 
			{
       	 			char *nenlace = malloc(info.st_size + 1);
        			readlink(path, nenlace, info.st_size + 1);
        			printf("%s->%s \n", act->d_name, nenlace);
        			free(nenlace);
	     		}
    		}

    		free(path);
    		act = readdir(dir);
  	}

  	closedir(dir);
  	return 0;
}
