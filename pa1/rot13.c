
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	if ((argc - 1) != 1) {
		return 0;
	}

  int lower = 97;
  int upper = 65;
  int count = 26;

  char *phrase = argv[1];
  int length = strlen(phrase);
  char encoded[length + 1];

  int i;
  for (i = 0; i < length; i++) {
    char c = phrase[i];
    if (c >= upper && c < (upper + count)) {
      c = upper + ((c - upper + 13) % count);
    }
    if (c >= lower && c < (lower + count)) {
      c = lower + ((c - lower + 13) % count);
    }
    encoded[i] = c;
  }
  encoded[length] = '\0';

	printf("%s\n", encoded);

	return 0;
}
