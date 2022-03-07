#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Name: Andrew Park
// netID: ap1614
// RUID: 186008936

struct dirent *readdir(DIR *dirp){
    char* envb = getenv("HIDDEN");
    char* env = malloc(strlen(envb)+1);
    strcpy(env, envb);
    struct dirent *(*real_rd)(DIR *) = dlsym(RTLD_NEXT, "readdir");
    struct dirent *retval = real_rd(dirp);
    if(env != NULL) {
        char* token;
        token = strtok(env, ":");
        while(retval != NULL && token != NULL) {
            if(!strcmp(token, retval->d_name)) {
                retval = real_rd(dirp);
            }
            token = strtok(NULL, ":");
        }
    }
    return retval;
}

