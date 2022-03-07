#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>

// Name: Andrew Park
// netID: ap1614
// RUID: 186008936

char FLAG = 0;

time_t time(time_t *tloc){
    time_t (*real_time)(time_t *) = dlsym(RTLD_NEXT, "time");
    if(!FLAG){
        FLAG = 1;
        if(tloc != NULL);
            *tloc=1621915200;
        return 1621915200;
    }
    return real_time(tloc);
}
