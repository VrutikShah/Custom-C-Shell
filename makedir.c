#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

// the function recurrsively makes directories given in the input.
// also takes multiple arguments
static void makeDir(const char *dir) {
        char tmp[256];
        char *p = NULL;
        size_t len;

        snprintf(tmp, sizeof(tmp),"%s",dir);
        len = strlen(tmp);
        if(tmp[len - 1] == '/')
                tmp[len - 1] = 0;
        for(p = tmp + 1; *p; p++)
                if(*p == '/') {
                        *p = 0;
                        mkdir(tmp, S_IRWXU);
                        *p = '/';
                }
        mkdir(tmp, S_IRWXU);                    //creating the directories
}
