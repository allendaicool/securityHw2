//
//  objgetacl.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#include "objgetacl.h"
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

/* This main function check if a certain usr have certain permssion
 * by checking the ACL file 
 */
int main(int argc, const char * argv[])
{
	/* uFlag stands for the user option
	 * gFlag stands for the group otion
	 * aFlag stands for the opertaion
	 * lFlag stands for -l option in objlist
	 */
	
	int  aFlag;
	int  lFlag;
	string usr("") ;
	string group("");
	char operation;
	int containBit;
	getUser_Group(usr,group);
	/* parse the argument passed in and did some sanity check
	 * on the user input
	 */
	aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,aFlag,lFlag,operation);
	/* check if some options exists. 
	For example -u and -g must appear in the user input */
	if(aFlag == 1 || lFlag == 1 || argc > 2){
		fprintf(stderr,"invalid argument input");
		exit(EXIT_FAILURE);
	}

	/* check if user and group combination exists in user+group file*/
	checkifUserGroup((char *)usr.c_str(), (char *)group.c_str(),0);	
	/* we do not allow shell redirect in the objget*/
	if(!checkShellRedirect()){
		fprintf(stderr,"don't allow shell redirect\n");		
		exit(EXIT_FAILURE);
	}


	string temp("filesystem/");


	containBit = checkIfContainPlus((char *)argv[argc-1]);
	
	if (containBit){	
		temp.append(argv[argc-1]);
		temp.append("+ACL");
	}
	else{
		temp.append(usr);
		if(sanityCheck((char *)argv[argc-1]) == 0){
			fprintf(stderr,"invalid filename argument");
			exit(EXIT_FAILURE);	
		}
		addPathName(temp,(char *)argv[argc-1],1,1,0);
	}


	char *val = NULL;
	/* find the permission list for certain group and user by reading ACL file*/
	findPermission(temp,(char *)usr.c_str(),(char *)group.c_str(),&val);
	if(val == NULL){
		printf("permission denied");
		exit(EXIT_FAILURE);
	}
	/* check if we have read permission to read the ACL*/
	int haveorNot  = checkPermission('v',val);
	if(haveorNot != 1)
	{
		fprintf(stderr,"do not have permission");
		exit(EXIT_FAILURE);
	}
	printf("\n %s\n ", val);
	free(val);
	return 0;
		
}
