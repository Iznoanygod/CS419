#ifndef _USERLIB_H_
#define _USERLIB_H_

enum error{SUCCESS, USER_EXISTS, USER_MISSING, BAD_PASSWORD, NO_SUCH_USER};

int add_user(char* username, char* password);

int authenticate(char* username, char* password);

#endif
