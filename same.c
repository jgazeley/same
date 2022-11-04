#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	if(argc != 3)                               // validate user input
	{
		fprintf(stderr, "Usage: %s file1 file2", argv[0]);
		exit(1);
	}
	
	FILE* f1 = fopen(argv[1], "rb");            // open first file
	if(!f1)
	{
		char errmsg[500];
		sprintf(errmsg, "Cannot open %s for reading", argv[1]);
		perror(errmsg);
		exit(1);
	}

	FILE* f2 = fopen(argv[2], "rb");            // open second file
	if(!f2)
	{
		char errmsg[500];
		sprintf(errmsg, "Cannot open %s for reading", argv[2]);
		perror(errmsg);
		exit(1);
	}

	while(!feof(f1))                            // compare each byte until EOF
	{
		if(getc(f1) != getc(f2))
		{
			printf("The files are not identical.");
			fclose(f1); fclose(f2);
			exit(0);
		}
	}

	printf("The files are identical.");
	fclose(f1); fclose(f2);
}