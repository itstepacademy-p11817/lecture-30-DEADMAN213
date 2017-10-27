/*
Написать функцию, которая получает указатель на статический массив и его размер. Функция распределяет
положительные, отрицательные и нулевые элементы в отдельные динамические массивы.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

uint8_t inputValue(const char* mes) {
	uint8_t val = 0;
	printf(mes);
	scanf("%hhu", &val);

	return val;
}

int8_t randomize(uint8_t val) {
	if (rand() % 2 == 0) {
		return rand() % val;
	}
	else {
		return -rand() % val;
	}
}

uint8_t* initMas(int8_t* mas, uint8_t size) {
	mas = (int8_t*)calloc(size, sizeof(uint8_t));

	for (uint8_t i = 0; i < size; i++) {
		mas[i] = randomize(26);
	}

	return mas;
}

uint8_t* printMas(int8_t* mas, uint8_t size) {
	if (mas == NULL) {
		return NULL;
	}

	printf("Massive: ");
	for (uint8_t i = 0; i < size; i++) {
		printf("%4hhi", mas[i]);
	}
	printf("\n");

	return mas;
}

bool findMas(int8_t* mas, int8_t val, uint8_t size) {
	for (uint8_t i = 0; i < size; i++) {
		if (*(mas + i) == val) {
			return true;
		}
	}

	return false;
}

int8_t* distributeMas(int8_t* first, int8_t* second, uint8_t** pos, uint8_t* sizes) {
	uint8_t maxsize = sizes[0];

	if (sizes[0] < sizes[1]) {
		maxsize = sizes[1];
	}

	for (uint8_t i = 0; i < maxsize; i++) {
		if (i < sizes[0] && *(first + i) > 0 && !findMas(*pos, *(first + i), sizes[2])) {
			*pos = (uint8_t*)realloc(*pos, ++sizes[2] * sizeof(uint8_t));
			*(*pos + sizes[2] - 1) = *(first + i);
		}

		if (i < sizes[1] && *(second + i) > 0 && !findMas(*pos, *(second + i), sizes[2])) {
			*pos = (uint8_t*)realloc(*pos, ++sizes[2] * sizeof(uint8_t));
			*(*pos + sizes[2] - 1) = *(second + i);
		}

	}

	return *pos;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Init massives.\n");
	printf("2 - Print massives.\n");
	printf("3 - Distribute massives.\n");
	printf("4 - Exit.\n");
	printf("Your choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	srand(time(NULL));

	uint8_t ch = 0;

	uint8_t sizes[3] = { 0 };

	int8_t* masfirst = NULL;
	int8_t* massecond = NULL;
	uint8_t* maspos = NULL;

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			if (masfirst) {
				free(masfirst);
				masfirst = NULL;
			}
			if (massecond) {
				free(massecond);
				massecond = NULL;
			}
			if (maspos) {
				free(maspos);
				maspos = NULL;
			}

			masfirst = initMas(masfirst, sizes[0] = inputValue("Input size of a first massive: "));
			massecond = initMas(massecond, sizes[1] = inputValue("Input size of a second massive: "));

			break;

		case 2:
			if (masfirst) {
				printf("First  ");
				printMas(masfirst, sizes[0]);
			}
			if (massecond) {
				printf("Second ");
				printMas(massecond, sizes[1]);
			}
			if (maspos) {
				printf("Distributed ");
				printMas(maspos, sizes[2]);
			}
			break;

		case 3:
			distributeMas(masfirst, massecond, &maspos, sizes);
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}
		printf("Done. Press any key.");
		_getch();
	}

	free(masfirst);
	free(massecond);
	free(maspos);

	return 0;
}