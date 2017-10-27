/*
Пользователь вводит диапазон чисел, найти в этом диапазоне все простые числа матричным способом.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>
#include <conio.h>

uint32_t inputValue(const char* mes) {
	uint32_t val = 0;
	printf(mes);
	scanf("%u", &val);

	return val;
}

uint32_t* initMas(uint32_t bgn, uint32_t end) {
	uint32_t* mas = (uint32_t*)calloc(end - bgn + 1, sizeof(uint32_t));

	for (uint32_t i = bgn; i <= end; i++) {
		*(mas + i - bgn) = i;
	}

	return mas;
}

uint32_t* printMas(uint32_t* mas, uint32_t size) {
	if (mas == NULL) {
		return NULL;
	}

	printf("Massive: ");
	for (uint32_t i = 0; i < size; i++) {
		printf("%4u", mas[i]);
	}
	printf("\n");

	return mas;
}

uint32_t getIndex(uint32_t* mas, uint32_t size, uint32_t val) {
	for (uint8_t i = 0; i < size; i++) {
		if (*(mas + i) == val) {
			return i;
		}
	}

	return size;
}

uint32_t* moveMas(uint32_t* mas, uint32_t end) {
	for (uint8_t i = 0; i < end; i++) {
		*(mas + i) = *(mas + i + 1);
	}

	return mas;
}

uint32_t* sive(uint32_t* mas, uint32_t* size, uint32_t bgn, uint32_t end) {
	uint8_t ind = 0;

	for (uint8_t i = 2; i <= sqrt(end); i++) {
		for (uint8_t j = i*i; j <= end; j += i) {
			if (j >= bgn && j <= end && (ind = getIndex(mas, *size, j)) < *size) {
				moveMas(mas + ind, *size - ind - 1);
				mas = (uint32_t*)realloc(mas, --*size * sizeof(uint32_t));
			}
		}
	}

	return mas;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Init massives.\n");
	printf("2 - Print massives.\n");
	printf("3 - Find all simple values.\n");
	printf("4 - Exit.\n");
	printf("Your choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	uint32_t size = 0;
	uint32_t ch = 0;
	uint32_t bgn = 0;
	uint32_t end = 0;
	uint32_t* mas = NULL;

	srand(time(NULL));

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			bgn = inputValue("Input begin: ");
			end = inputValue("Input end: ");
			size = end - bgn + 1;

			if (mas) {
				free(mas);
				mas = NULL;
			}

			mas = initMas(bgn, end);
			break;

		case 2:
			printMas(mas, size);
			break;

		case 3:
			sive(mas, &size, bgn, end);
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}
		printf("Done. Press any key.");
		_getch();
	}

	free(mas);

	return 0;
}