#include <stdio.h>
#include <stdint.h>

typedef _Bool bool;
typedef uint32_t uint;

uint bit (const uint numb, const uint shift){
    return (uint)((numb & (1 << shift)) >> shift);
}

uint isItCharUTF(const uint count_bytes){
    if (count_bytes == 0)
        return 1;

    char c = getchar();

    if (c == -1)
        return 0;

    if (bit(c, 7) == 1 && bit(c, 6) == 0){
        return isItCharUTF(count_bytes-1);
    } else {
        return 0;
    }
}

int main() {
	char c;

    uint ASCIIcount = 0;
    uint UTFcount = 0;

    while (1){
        uint bytesForCheck = 0;
        c = getchar();

        if (c == -1)
            break;

        if (bit(c, 7) == 0) {
            ASCIIcount++;
            continue;
        } else if (bit(c, 7) == 1 && bit(c, 6) == 1 && bit(c, 5) == 0){
            bytesForCheck = 1;
        } else if (bit(c, 7) == 1 && bit(c, 6) == 1 && bit(c, 5) == 1 && bit(c, 4) == 0){
            bytesForCheck = 2;

        } else if (bit(c, 7) == 1 && bit(c, 6) == 1 && bit(c, 5) == 1 && bit(c, 4) == 1 && bit(c, 3) == 0)
            bytesForCheck = 3;
        else
            continue;

        if (isItCharUTF(bytesForCheck))
            UTFcount++;
        else {
            printf("%u %u", ASCIIcount, UTFcount);
            return 1;
        }
    }

    printf("%u %u", ASCIIcount, UTFcount);
    return 0;
}
