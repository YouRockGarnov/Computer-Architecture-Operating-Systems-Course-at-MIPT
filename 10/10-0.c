//10-0
#define _FILE_OFFSET_BITS 64
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char current_file_name[PATH_MAX];
    uint64_t overall_size = 0;
    struct stat st;
    char * nl;
    while (fgets(current_file_name, sizeof(current_file_name), stdin)){
        nl = memchr(current_file_name, '\n', sizeof(current_file_name));
        if (nl) {
            *nl = '\0';
        }
        if (-1!=lstat(current_file_name, &st)) {
            if (S_ISREG(st.st_mode)) {
                overall_size += st.st_size;
            }
        }
    }

    printf("%"PRIu64"\n", overall_size);
}
