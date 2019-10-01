#define _FILE_OFFSET_BITS 64

#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main() {
	struct stat st;
	ssize_t input_read;
	char file_name[PATH_MAX];
	char headers[PATH_MAX + 2];

	while (fgets(file_name, sizeof(file_name), stdin)) {
		char* nl;

		nl = memchr(file_name, '\n', sizeof(file_name));
		if (nl)
			*nl = '\0';

		if (-1 != lstat(file_name, &st)) {
			if (!(S_IXUSR & st.st_mode))
				continue;

			int in = open(file_name, O_RDONLY);
			if (in == -1)
				continue;

			ssize_t read_count = 0;
			for (input_read = read(in, (char*) headers + read_count, sizeof(headers) - read_count); read_count < sizeof(headers);) {
				read_count += input_read;

				if (input_read == -1 || input_read == 0)
					break;
			}

			nl = memchr(headers, '\n', sizeof(headers));
            if (nl)
                *nl = '\0';


			if (strlen(headers) >= 2)
		        if (headers[0] == '#' && headers[1] == '!')
		            if (lstat(headers + 2, &st) != -1)
		                if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		                    goto finally;


			if (strlen(headers) >= 4)
				if (headers[0] == (char)127 && headers[1] == 'E' && headers[2] == 'L' && headers[3] == 'F')
					goto finally;


			printf("%s\n", file_name);

			finally:
				close(in);
		}
	}

	return 0;
}
