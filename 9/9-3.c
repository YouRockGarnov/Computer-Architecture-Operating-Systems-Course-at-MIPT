#include <stdint.h>
#include <windows.h>
#include <stdio.h>

struct Item
{
	int value;
	uint32_t next_pointer;
};


int main(int argc, char* argv[]) {
	HANDLE in = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD bytes_read = 0;
	struct Item in_struct;
	ReadFile(in, &in_struct, sizeof(struct Item), &bytes_read, NULL);

	if (bytes_read > 0) {
		int next_pointer = in_struct.next_pointer;

		printf("%d ", in_struct.value);
		while (next_pointer != 0) {
			SetFilePointer(in, next_pointer, NULL, FILE_BEGIN);
			ReadFile(in, &in_struct, sizeof(struct Item), &bytes_read, NULL);

			printf("%d ", in_struct.value);

			next_pointer = in_struct.next_pointer;
		}
	}

	CloseHandle(in);

	return 0;
}
