#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

int sameSize(char* file1, char* file2);
void openFiles(FILE** f1, FILE** f2, char* arg1, char* arg2);

int main(int argc, char* argv[])
{
	if(argc != 3)                               // validate user input
	{
		fprintf(stderr, "Usage: %s file1 file2", argv[0]);
		exit(1);
	}

	if(!sameSize(argv[1], argv[2]))				// check file sizes
	{
		printf("File sizes do not match. The files are not identical.");
		exit(0);
	}
	
	FILE *f1, *f2;								// open files if sizes match
	openFiles(&f1, &f2, argv[1], argv[2]);

	while(!feof(f1))                            // compare each byte until EOF
	{
		if(getc(f1) != getc(f2))
		{
			printf("Binary data does not match. The files are not identical.");
			fclose(f1); fclose(f2);
			exit(0);
		}
	}

	printf("The files are identical.");
	fclose(f1); fclose(f2);
}

// returns 1 if file1 and file2 are the same size, otherwise returns 0
int sameSize(char* file1, char* file2)
{
	struct stat file1info, file2info;
	
	stat(file1, &file1info);	size_t file1size = file1info.st_size;
	stat(file2, &file2info);	size_t file2size = file2info.st_size;

	if(file1size != file2size)
		return 0;

	else return 1;
}

// opens input files for reading; displays an error message if there is a problem opening a file
void openFiles(FILE** f1, FILE** f2, char* arg1, char* arg2)
{
	*f1 = fopen(arg1, "rb");          	    // open first file
	if(!f1)
	{
		char errmsg[500];
		sprintf(errmsg, "Cannot open %s for reading", arg1);
		perror(errmsg);
		exit(1);
	}

	*f2 = fopen(arg2, "rb");                  // open second file
	if(!f2)
	{
		char errmsg[500];
		sprintf(errmsg, "Cannot open %s for reading", arg2);
		perror(errmsg);
		exit(1);
	}
}