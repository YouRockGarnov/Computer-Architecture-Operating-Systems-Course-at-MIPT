
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char* argv){
  int t_year, t_mon, t_day, t_hour, t_min, t_sec;
  struct tm time;

  time_t prev = -42;
  time_t cur = -42;

  while(scanf("%d-%d-%d %d:%d", &t_year, &t_mon, &t_day, &t_hour, &t_min) != EOF){
    memset(&time, 0, sizeof(time));

    time.tm_year = t_year - 1900;
    time.tm_mon = t_mon - 1;
    time.tm_mday = t_day;
    time.tm_hour = t_hour;
    time.tm_min = t_min;
    time.tm_isdst = -1;

    if (prev == -42)
      prev = mktime(&time);
    else{
      cur = mktime(&time);

      printf("%d\n", (cur - prev) / 60);
      prev = cur;
    }
  }

  return 0;
}
