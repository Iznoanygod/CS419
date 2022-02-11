#include "userlib.h"
#include "autherror.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int add_user(char* username, char* password) {
    FILE *fp = fopen("users.txt", "a+");
    char user[512];
    while(fscanf(fp, "%s %*[^\n]\n", user) != EOF) {
        if(!strcmp(user, username)){
            return USER_EXISTS;
        }
    }
    fprintf(fp, "%s %s\n", username, password);
    return SUCCESS;
}

int authenticate(char* username, char* password) {
    FILE *fp = fopen("users.txt", "a+");
    char user[512];
    char pass[512];
    while(fscanf(fp, "%s %[^\n]\n", user, pass) != EOF) {
        if(!strcmp(user, username)){
            if(!strcmp(pass, password)){
                return SUCCESS;
            }
            else
                return BAD_PASSWORD;
        }
    }
    return NO_SUCH_USER;
}
