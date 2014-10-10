//
//  functionCall.h
//  
//
//  Created by yihong dai on 9/20/14.
//
//

#ifndef ____functionCall__
#define ____functionCall__
#include<string>
using namespace std;
int parseCommand(int , const char ** , int & , int &,int &,int &,
		 string &, string &, char &);
int findPermission(string & ,char *,char  *, char **);
int checkPermission(char, char *);
int addPathName(string &, char *, int , int, int);
int checkShellRedirect();
bool isdefaultPermission(char );
int checkMatch ( char *  , char *, char *, char *);
int checkifUserGroup (char *, char *,int);
int sanityCheck(char  *);
int checkIfContainPlus(char *);
#endif /* defined(____functionCall__) */
