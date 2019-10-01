#define _FILE_OFFSET_BITS 64

#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


 char file_name[PATH_MAX];

 void set_nl(){
  char* nl;
  nl = memchr(file_name, '\n', sizeof(file_name));
    if (nl)
      *nl = '\0';
 }

 void print_abs_path(){
   char* symlink_path = realpath(file_name, NULL);
   printf("%s\n", symlink_path);
   free(symlink_path);
 }

 void create_link(){
    static const char* pref = "link_to_";
    static char links[PATH_MAX];

    links[0] = '\0';
    strncat(links, pref, strlen(pref));
    char* pos = strrchr(file_name, '/');
    strncat(links, pos + 1, strlen(pos + 1));
    symlink(file_name, links);
 }

int main() {
    struct stat st;

    while (fgets(file_name, sizeof(file_name), stdin)){
        set_nl();

        if (-1!=lstat(file_name, &st)) {
            if (S_ISLNK(st.st_mode))
                print_abs_path(file_name);

            else if (S_ISREG(st.st_mode))
                create_link(file_name);
        }
      }

    return 0;
}
