#include "accesslib.h"
#include "autherror.h"
#include "domainlib.h"
#include "typelib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_access(char* operation, char* domain, char* type) {
    FILE *fp = fopen("access_control_matrix.txt", "a+");
    char op[512], dom[512], ty[512];
    while(fscanf(fp, "%s %s %s\n", op, dom, ty) != EOF){
        if(!strcmp(op, operation) && !strcmp(dom, domain) && !strcmp(ty, type)){
            return SUCCESS;
        }
    }
    fprintf(fp, "%s %s %s\n", operation, domain, type);
    return SUCCESS;
}

int can_access(char* operation, char* user, char* object){
    FILE *fp = fopen("access_control_matrix.txt", "r");
    if(fp == NULL)
        return 0;
    char op[512];
    char domain[512];
    char type[512];

    while(fscanf(fp, "%s %s %s\n", op, domain, type) != EOF) {
        if(strcmp(op, operation))
            continue;
        if(!in_type(object, type))
            continue;
        if(!in_domain(user, domain))
            continue;
        return SUCCESS;
    }
    return ACCESS_DENIED;
}

