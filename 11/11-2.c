#include <sys/stat.h>
#include <stdio.h>
#include <ftw.h>

static int sum = 0;

int summarize(const char* path, const struct stat* st, int typeflag){
  if (S_ISREG(st->st_mode))
    sum += st->st_size;

  return 0;
}

int main(int argc, char** argv){
  ftw(argv[1], &summarize, 1);

  printf("%d", sum);
  return 0;
}
