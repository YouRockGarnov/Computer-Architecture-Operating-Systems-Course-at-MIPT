#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char const *argv[]) {
  int in = open(argv[1], O_RDONLY, 0640);
  int exit_flag = 0;

  if (-1 == in) {
    goto finally;
  }

  ssize_t in_read;
  struct Item item;
  while ((in_read=read(in, &item, sizeof(struct Item)))>0){
    printf("%d ", item.value);

      if (item.next_pointer > 0) {
        off_t result = lseek(in, item.next_pointer, SEEK_SET);

        if (result == -1){
          exit_flag = 1;
          goto finally;
        }


      } else {
      goto finally;
    }
  }

  finally:
    close(in);

  return exit_flag;
}
