#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>

void print(char* from, char* to) {
	while (*from != '\0') {
		*to = *from;
		from++;
		to++;
	}

	*to = '\0';
}

int remove_dir(char* path, int i) {
	i--;
	path[i] = '\0';
	i--;

	while (path[i] != '/') {
		path[i] = '\0';
		i--;
	}

	path[i] = '\0';

	return i;
}

extern void normalize_path(char* path) {
	char* ptr = path;

	int slash_flag = 0;
	int point_flag = 0;

	char out[1000000];
	int i = 0;

	while (*ptr != '\0') {
		char ch = *ptr;

		if (ch == '/') {
			if (slash_flag == 0 && point_flag == 0) {
				out[i] = ch;
				i++;
			}

			slash_flag = 1;
			point_flag = 0;

			//point_flag doesn't matter
		} else if (ch == '.') {
			if (point_flag) {
				i = remove_dir(out, i);
				point_flag = 0;
			}
			else
				point_flag = 1;

			slash_flag = 0;

		} else {
			point_flag = 0;
			slash_flag = 0;
			out[i] = ch;
			i++;
		}

		ptr++;
	}

	out[i] = '\0';
	print(out, path);
}

/*int main() {
	using namespace std;

	char* in = new char[1000];
	int i = 0;

	char ch;
	cin >> ch;
	while (ch != '#') {
		in[i] = ch;
		i++;
		cin >> ch;
	}

	in[i] = '\0';

	normalize_path(in);

	i = 0;
	ch = in[0];
	while (ch != '\0') {
		cout << ch;
		i++;
		ch = in[i];
	}

	system("pause");

	return 0;
}*/
