#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "userlib.h"
#include "domainlib.h"
#include "autherror.h"
#include "accesslib.h"
#include "typelib.h"

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
        if(argc > 4) {
            status_print(ARG_TOO_MANY);
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
            status_print(ARG_TOO_MANY);
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
    if(!strcmp(argv[1], "SetDomain")){
        if(argc > 4) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 3) {
            status_print(MISSING_DOMAIN);
            return 0;
        }
        char* username = argv[2];
        char* domain = argv[3];
        if(!strcmp(domain, "")){
            status_print(MISSING_DOMAIN);
            return 0;
        }
        if(!strcmp(username, "")){
            status_print(USER_MISSING);
            return 0;
        }
        int code = set_domain(username, domain);
        status_print(code);
        return 0;
    }
    if(!strcmp(argv[1], "DomainInfo")) {
        if(argc > 3) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 3) {
            status_print(MISSING_DOMAIN);
            return 0;
        }
        char* domain = argv[2];
        if(!strcmp(domain, "")){
            status_print(MISSING_DOMAIN);
            return 0;
        }
        domain_info(domain);
        return 0;
    }
    if(!strcmp(argv[1], "SetType")) {
        if(argc > 4) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 4) {
            status_print(MISSING_TYPE);
            return 0;
        }
        char* object = argv[2];
        char* type = argv[3];
        if(!strcmp(object, "")){
            status_print(MISSING_OBJECT);
            return 0;
        }
        if(!strcmp(type, "")){
            status_print(MISSING_TYPE);
            return 0;
        }
        int code = set_type(object, type);
        status_print(code);
        return 0;
    }
    if(!strcmp(argv[1], "TypeInfo")) {
        if(argc > 3) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 3) {
            status_print(MISSING_TYPE);
            return 0;
        }
        char* type = argv[2];
        if(!strcmp(type, "")){
            status_print(MISSING_TYPE);
            return 0;
        }
        type_info(type);
        return 0;
    }
    if(!strcmp(argv[1], "AddAccess")){
        if(argc > 5) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 5) {
            status_print(MISSING_TYPE);
        }
        char* operation = argv[2];
        char* domain = argv[3];
        char* type = argv[4];
        if(!strcmp(operation, "")) {
            status_print(MISSING_OPERATION);
            return 0;
        }
        if(!strcmp(domain, "")) {
            status_print(MISSING_DOMAIN);
            return 0;
        }
        if(!strcmp(type, "")) {
            status_print(MISSING_TYPE);
            return 0;
        }
        int code = add_access(operation, domain, type);
        status_print(code);
        return 0;
    }
    if(!strcmp(argv[1], "CanAccess")){
        if(argc > 5) {
            status_print(ARG_TOO_MANY);
            return 0;
        }
        if(argc < 5) {
            status_print(MISSING_TYPE);
        }
        char* operation = argv[2];
        char* user = argv[3];
        char* object = argv[4];
        if(!strcmp(operation, "")) {
            status_print(MISSING_OPERATION);
            return 0;
        }
        if(!strcmp(user, "")) {
            status_print(USER_MISSING);
            return 0;
        }
        if(!strcmp(object, "")) {
            status_print(MISSING_OBJECT);
            return 0;
        }
        int code = can_access(operation, user, object);
        status_print(code);
        return 0;
    }
    status_print(INVALID_COMMAND);
    return 0;
}

void status_print(int status) {
    if(status == SUCCESS) {
        printf("Success\n");
        return;
    }
    if(status == ACCESS_DENIED) {
        printf("Error: acccess denied\n");
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
    if(status == ARG_TOO_MANY) {
        printf("Error: too many arguments\n");
        return;
    }
    if(status == MISSING_DOMAIN) {
        printf("Error: missing domain\n");
        return;
    }
    if(status == MISSING_OPERATION) {
        printf("Error: missing operation\n");
        return;
    }
    if(status == MISSING_TYPE) {
        printf("Error: missing type\n");
        return;
    }
    if(status == MISSING_OBJECT) {
        printf("Error: missing object\n");
        return;
    }
    if(status == INVALID_COMMAND) {
        printf("Error: invalid command\n");
        return;
    }
}

