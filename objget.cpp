//
//  objget.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objget.h"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include "functionCall.h"

using namespace std;

/* This main function parse the use input and does the sanity check
 *  on input, and display the file content in the stdout if we have permission
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
	int readPermission;
	char *val;
	int containBit;
	FILE *filestream;

	/* parse the argument passed in and did some sanity check
	 * on the user input
	 */
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		fprintf(stderr, "invalid argument input");
		exit(EXIT_FAILURE);
	}
	/* check if user and group combination exists in user+group file*/
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);

	/* we do not allow shell redirect in the objget*/
	if(!checkShellRedirect()){
		fprintf(stderr,"don't allow shell redirect\n");		
		exit(EXIT_FAILURE);
	}
	/* append string after the username and get a new string
	 * for example user+doc1 as name for doc file for user*/
	string fileName("");

	
	containBit = checkIfContainPlus((char *)argv[argc-1]);
	
	if (containBit){
				
		fileName.append(argv[argc-1]);
		fileName.append("+ACL");
	}
	else{
		fileName.append(usr);
		addPathName(fileName,(char *)argv[argc-1],1,0,0);
	}
	
	

	string fileNameACL(fileName);
	if (!containBit)
		addPathName(fileNameACL,NULL,0,1,0);
	val = NULL;

	/* find if we have permission to display the file*/
	findPermission(fileNameACL, (char *)usr.c_str(),(char *)group.c_str()
		       ,&val);
	if(val == NULL){
		printf("permission denied");
		exit(EXIT_FAILURE);
	}
	
	readPermission = checkPermission('r',val);
	free(val);
	/* if we have permssion, then we display the file content in stdout*/
	if(readPermission == 1){
		filestream = fopen(fileName.c_str(),"r");
		if(filestream == NULL){
			printf("no suc file\n");
			exit(EXIT_FAILURE);
		}
		char *buffer = NULL;;
		size_t dum;
		int revalue;
		puts("\n");
		while((revalue = (int)getline(&buffer,&dum,filestream))!= -1)
		{
			puts(buffer);
		}
		if(buffer)
			free(buffer);
		fclose(filestream);
	}
	else{
		fprintf(stderr,"we dont have read permssion");
		exit(EXIT_FAILURE);
	}
	
	return 0;
	
}
