//
//  objtestacl.cpp
//  
//
//  Created by yihong dai on 9/21/14.
//
//

#include "objtestacl.h"
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
	int  uFlag;
	int  gFlag ;
	int  aFlag;
	int  lFlag;
	string usr ;
	string group;
	char operation;
	char *val;
	int containBit;

	/* parse the argument passed in and did some sanity check
	 * on the user input
	 */
	uFlag = 0, gFlag = 0, aFlag = 0,lFlag = 0 ;
	parseCommand(argc,argv,uFlag,gFlag,aFlag,lFlag,usr
			      , group,operation);
 	/* check if some options exists. 
	For example -u and -g must appear in the user input */
	if(uFlag != 1 || gFlag!= 1 || aFlag != 1 || lFlag == 1){
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


	string temp("");
	containBit = checkIfContainPlus((char *)argv[argc-1]);
	if (containBit){	
		temp.append(argv[argc-1]);
		temp.append("+ACL");
	}
	else{
		temp.append(usr);
		addPathName(temp,(char *)argv[argc-1],1,1,0);
	}
	val = NULL;

	/* find the permission list for certain group and user by reading ACL file*/
	findPermission(temp,(char *)usr.c_str(),(char *)group.c_str(),&val);
	if(val == NULL){
		printf("permission denied");
		exit(EXIT_FAILURE);
	}
	/* check if a certain permission exists in the permission list*/
	int haveorNot  = checkPermission(operation,val);
	free(val);
	if(haveorNot!= 1)
	{
		printf("\ndenied\n");
		return 0;
	}
	printf("\nallowed\n");
	return 0;

}
