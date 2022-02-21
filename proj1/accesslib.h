#ifndef _ACCESS_LIB_H_
#define _ACCESS_LIB_H_

int add_access(char* operation, char* domain, char* type);

int can_access(char* operation, char* user, char* object);

#endif
