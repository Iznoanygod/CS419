#ifndef _USERLIB_H_
#define _USERLIB_H_

int add_user(char* username, char* password);

int authenticate(char* username, char* password);

int user_exists(char* username);

#endif
