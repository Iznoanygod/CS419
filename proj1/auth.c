#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "userlib.h"
#include "autherror.h"

void status_print(int status);

int main(int argc, char** argv) {
    if(argc == 1) {
        printf("Invalid argument count\n");
        return 0;
    }
    if(!strcmp(argv[1], "AddUser")) {
        if(argc < 3) {
            status_print(USER_MISSING);
            return 0;
        }
        char* username = argv[2];
        if(!strcmp(username, "")){
            status_print(USER_MISSING);
            return 0;
        }
        char* password;
        if(argc > 3) {
            password = argv[3];
        }
        else {
            password = "";
        }
        int code = add_user(username, password);
        status_print(code);   
        return 0;
    }
    if(!strcmp(argv[1], "Authenticate")){
        if(argc > 4) {
            printf("Error: too many arguments for Authenticate\n");
            return 0;
        }
        if(argc < 3) {
            status_print(USER_MISSING);
            return 0;
        }
        char* username = argv[2];
        if(!strcmp(username, "")){
            status_print(USER_MISSING);
            return 0;
        }
        char* password;
        if(argc > 3) {
            password = argv[3];
        }
        else {
            password = "";
        }
        int code = authenticate(username, password);
        status_print(code);
        return 0;
    }

    return 0;
}

void status_print(int status) {
    if(status == SUCCESS) {
        printf("Success\n");
        return;
    }
    if(status == USER_EXISTS) {
        printf("Error: user exists\n");
        return;
    }
    if(status == USER_MISSING) {
        printf("Error: username missing\n");
        return;
    }
    if(status == BAD_PASSWORD) {
        printf("Error: bad password\n");
        return;
    }
    if(status == NO_SUCH_USER) {
        printf("Error: no such user\n");
        return;
    }
}

