#include "typelib.h"
#include "autherror.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int set_type(char* object, char* type) {
    char type_file[512];
    snprintf(type_file, 512, "%s_type.txt", type);
    FILE *fp = fopen(type_file, "a+");
    char obj[512];
    while(fscanf(fp, "%[^\n]\n", object) != EOF) {
        if(!strcmp(obj, object)){
            fclose(fp);
            return SUCCESS;
        }
    }
    fprintf(fp, "%s\n", object);
    fclose(fp);
    return SUCCESS;
}

void type_info(char* type) {
    char type_file[512];
    snprintf(type_file, 512, "%s_type.txt", type);
    FILE *fp = fopen(type_file, "r");
    if(fp == NULL)
        return;
    char object[512];
    while(fscanf(fp, "%[^\n]\n", object) != EOF) {
        printf("%s\n", object);
    }
    fclose(fp);
}
