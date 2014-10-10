/*****************************************************
 * FILE NAME: help.cpp
 *
 * Created on: Sept 25 2014
 * Author: Yihong Dai
 * this function creates new file for specified user
 *****************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include "help.h"
#include "functionCall.h"
using namespace std;

/* This main function parse the use input and does the sanity check
 *  on input, and  create a file or overwrite a file if certain 
 * permission is possessed by the specified user. 
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
	/* the usr, operation and group store the user inputs 
	 * and several file steams are created to open or overwrite
	 * the file 		
	 */
	string usr ;
	string group;
	char operation;
	string fileNameACL;
	char *storeVal;
	int overWritePermission;
	FILE *newFile ;
	FILE *filestream;
	int val ;
	size_t dum;
	char *bufferReadIn;
	FILE *aclList;
	int overWrite;
	/* parse the argument passed in and did some sanity check
	 * on the user input
	 */	
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0, overWrite = 0;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
		     ,group,operation);
	
	/* check if user and group combination exists in user+group file*/
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);
	
	/* check if some options exists. 
	 *For example -u and -g must appear in the user input */
	if(uFlag != 1 || gFlag!= 1 || aFlag == 1 || lFlag == 1){
		fprintf(stderr, "invalid argument input\n");		
		//perror("invalid argument input");
		exit(EXIT_FAILURE);
	}
	/*check if the shell has been redirected */	
	if(checkShellRedirect()){
		fprintf(stderr,"There is no shell redirect.  stopped\n");		
		exit(EXIT_FAILURE);
	}

	/* append string after the username and get a new string
	 * for example user+doc1 as name for doc file for user*/
	string fileName(usr);
	addPathName(fileName,(char *)argv[argc-1],1,0,0);
	
	
	storeVal = NULL;
	filestream = fopen(fileName.c_str(),"r");
	if(filestream != NULL){
		overWrite = 1;
		fileNameACL.assign(fileName);
		addPathName(fileNameACL,NULL,0,1,0);
		
		/*find if we have permission to overwrite the existing file
  		 * allowed when there is p character among the action list*/
		findPermission(fileNameACL, (char *)usr.c_str(),
			       (char *)group.c_str(),&storeVal);
		if(storeVal == NULL){
			fprintf(stderr, "no usr group combo in the ACL\n");		
			fprintf(stderr, "someone modified the ACL file\n");
			exit(EXIT_FAILURE);
		}	
		/* check if permssion is contained among the permission list
		 */	
		overWritePermission = checkPermission('w',storeVal);
		free(storeVal);
		fclose(filestream);
		if(overWritePermission != 1){
			fprintf(stderr, "we dont have overwrite permssion\n");
			exit(EXIT_FAILURE);
		}
	}
	
	newFile = fopen(fileName.c_str(),"w+");
	
	if(newFile == NULL)
		exit(EXIT_FAILURE);
	
	bufferReadIn = NULL;
	/* read file contents from the input file into the usr file
	 */
	while((val = (int)getline(&bufferReadIn,&dum,stdin))!=-1){
		fputs(bufferReadIn,newFile);
		free(bufferReadIn);
		bufferReadIn = NULL;
	}
	fclose(newFile);
	/* creates a new aclFile for the created file
	 */
	if(overWrite == 0){
		string aclListName(fileName);
		addPathName(aclListName,NULL,0,1,0);	
		aclList = fopen(aclListName.c_str(),"w+");
		if(aclList == NULL)
			exit(EXIT_FAILURE);
		fputs(usr.c_str(),aclList);
		fputs(".*	",aclList);
		fputs("rwxpv", aclList);
		fclose(aclList);
	}
	/*
	printf ("uflag = %d,aflag = %d, gflag = %d, lvalue = %d\n",
		uFlag,aFlag, gFlag, lFlag);
	printf("uval = %s, gVal = %s, aVal = %c", usr.c_str(),group.c_str(),
	       operation);*/
	return 0;
}




