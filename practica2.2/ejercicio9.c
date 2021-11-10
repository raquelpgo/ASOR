#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Especifique la ruta del fichero!\n");
		return -1;
	}

	struct stat buf;

	if (stat(argv[1], &buf) != 0)
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;	
	}
	
	char* tipo = "otro tipo";
	if (S_ISDIR(buf.st_mode))
	{
		tipo="directorio";
	}

	else if(S_ISREG(buf.st_mode))
	{
		tipo="fichero ordinario";
	}

	else if(S_ISLNK(buf.st_mode))
	{
		tipo="enlace simbólico";
	}

	
	struct tm *t = localtime(&(buf.st_atim.tv_sec));

	printf("Major: %li\nMinor: %li\nNº Inodo: %li\nTipo de fichero: %s\nHora de último acceso: %d:%d\n"
		,(long)major(buf.st_dev),(long)minor(buf.st_dev),buf.st_ino,tipo,t->tm_hour,t->tm_min);


	//LA DIFERENCIA ENTRE ST_MTIME Y ST_CTIME ES QUE LA PRIMERA GUARDA LA INFORMACIÓN DE LA FECHA DE LA ULTIMA MODIFICIACION Y LA SEGUNDA DE LA DE CREACIÓN
	return 0;
}
