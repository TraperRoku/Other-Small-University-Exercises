// PS IS1 320 LAB02 
// Filip Kaźmierczak 
// kf53844@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <utmpx.h>

void printLoginUser(){
 struct utmpx *entry;
 struct passwd *pw;

 setutxent();

 while((entry = getutxent()) != NULL){
  if (entry->ut_type == USER_PROCESS) {
   pw = getpwnam(entry->ut_user);
   if(pw){
    printf("%d (%s) %s %s\n", pw->pw_uid, entry->ut_user, entry->ut_line, entry->ut_host);
   }
   }

 }
 endutxent();
}
