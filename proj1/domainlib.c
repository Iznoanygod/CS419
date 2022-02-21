#include "domainlib.h"
#include "userlib.h"
#include "autherror.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int set_domain(char* username, char* domain) {
    if(!user_exists(username)) {
        return NO_SUCH_USER;
    }
    char domain_file[512];
    snprintf(domain_file, 512, "%s_domain.txt", domain);
    FILE *fp = fopen(domain_file, "a+");
    char user[512];
    while(fscanf(fp, "%[^\n]\n", user) != EOF){
        if(!strcmp(user, username)){
            fclose(fp);
            return SUCCESS;
        }
    }
    fprintf(fp, "%s\n", username);
    fclose(fp);
    return SUCCESS;
}

int in_domain(char* username, char* domain) {
    char domain_file[512];
    snprintf(domain_file, 512, "%s_domain.txt", domain);
    FILE *fp = fopen(domain_file, "r");
    if(fp == NULL)
        return 0;
    char user[512];
    while(fscanf(fp, "%[^\n]\n", user) != EOF) {
        if(!strcmp(user,username))
            return 1;
    }
    return 0;
}

void domain_info(char* domain) {
    char domain_file[512];
    snprintf(domain_file, 512, "%s_domain.txt", domain);
    FILE *fp = fopen(domain_file, "r");
    if(fp == NULL)
        return;
    char username[512];
    while(fscanf(fp, "%[^\n]\n", username) != EOF) {
        printf("%s\n", username);
    }

    fclose(fp);
}
