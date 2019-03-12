
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
	if ((argc - 1) != 1) {
		return 0;
	}

  char *phrase = argv[1];
  int olength = strlen(phrase);
	int plength = 2 * olength;
  char *parsed = malloc((plength + 1) * sizeof(char));

	int i, j, count = 1, pos = 0;
	for (i = 0; i < olength;) {
		if (phrase[i] >= '0' && phrase[i] <= '9') {
			printf("error\n");
			return 0;
		}
		for (j = i + 1; j < olength; j++) {
			if (phrase[j] != phrase[i]) {
				break;
			}
			count++;
		}

		int remaining = (plength + 1) - pos;
		int size = snprintf(parsed + pos, remaining, "%c%d", phrase[i], count);
		pos += size;
		if (pos > olength) {
			parsed = phrase;
			break;
		}
		i += count;
		count = 1;
	}

	parsed[olength] = '\0';

	printf("%s\n", parsed);

	return 0;
}
