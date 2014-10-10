//
//  objlist.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objlist.h"
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
	/* uFlag stands for the user option
	 * gFlag stands for the group otion
	 * aFlag stands for the opertaion
	 * lFlag stands for -l option in objlist
	 */
	int  uFlag;
	int  gFlag ;
	int  aFlag;
	int  lFlag;
	string usr ;
	string group;
	char operation;
	struct dirent *entry;
	struct stat st;;
	
	/* parse the argument passed in and did some sanity check
	 * on the user input
	 */
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	/* check if some options exists. 
	For example -u and -g must appear in the user input */
	if(uFlag != 1 || gFlag== 1 || aFlag == 1 ){
		fprintf(stderr,"invalid argument input");
		exit(EXIT_FAILURE);
	}

	/* check if user and group combination exists in user+group file*/
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),1);	
	/* we do not allow shell redirect in the objget*/
	if(!checkShellRedirect()){
		fprintf(stderr,"don't allow shell redirect\n");		
		exit(EXIT_FAILURE);
	}
	/* open the current directory to iterate all the files
	 * contained in that folder and search for the file 
	 * belonged to the user.
	 */
	DIR *currentDir;
	char *currentDirName = (char *)"./";
	if ((currentDir = opendir(currentDirName)) == NULL){
		fprintf(stderr,"opendir() error");
		exit(EXIT_FAILURE);
	}

	/* ignore the ACL file other file
	 * prints off the filename and maybe its size*/
	while ((entry = readdir(currentDir)) != NULL )
	{
		if(strstr(entry->d_name,usr.c_str()) != NULL &&
		   strstr(entry->d_name,"ACL") == NULL&&
		   strstr(entry->d_name,"meta") == NULL){
			int size;
			stat(entry->d_name, &st);
			size = (int)st.st_size;
			char * toBeprint = (char *)malloc(sizeof(char)*(
					strlen(entry->d_name)+1));
			strcpy(toBeprint,entry->d_name);
			toBeprint[strlen(entry->d_name)] = '\0';
					
			char *limiter = (char *)"+";
			char *firstName = strtok(toBeprint,limiter);
			firstName = strtok(NULL,limiter);
			if(lFlag)
				printf("\n %s     %d bytes \n",firstName,size);
			else
				printf("\n %s \n ",firstName);

			if(toBeprint)
				free(toBeprint);
		}
	}
	return 0 ;
}
