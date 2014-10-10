
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include "functionCall.h"

using namespace std;

/* This main function lists all the file possessed by
 * certain usr and might display the file size as well
 */
int main(int argc, const char * argv[])
{
	FILE *filestream;
	char *bufferReadIn;
	filestream = fopen("user+group","w+");
	char *delimiter;
	char *user;
	if(filestream == NULL)
		fprintf(stderr,"something happends");
	bufferReadIn = NULL;

	/* dump the content from user input file into ACL file*/
	while((value = (int)getline(&bufferReadIn,&dum,stdin))!=-1){
		user = strtok(bufferReadIn,delimiter);
		
		token2 = strtok(NULL,delimiter);	
		free(bufferReadIn);
		bufferReadIn = NULL;
	}
	fclose(filestream);

}
