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

uint8_t* initMas(uint8_t size) {
	int8_t* mas = (int8_t*)calloc(size, sizeof(uint8_t));

	for (uint8_t i = 0; i < size; i++) {
		mas[i] = randomize(10);
	}

	return mas;
}

uint8_t* printMas(int8_t* mas, uint8_t size) {
	if (mas == NULL) {
		return NULL;
	}

	printf("Massive: ");
	for (uint8_t i = 0; i < size; i++) {
		printf("%3hhi", mas[i]);
	}
	printf("\n");

	return mas;
}

uint8_t* distributeMas(int8_t* mas, int8_t** negMas, int8_t** zeroMas, int8_t** posMas, uint8_t* sizes) {
	for (uint8_t i = 0; i < sizes[0]; i++) {
		if (*(mas + i) < 0) {
			*negMas = (int8_t*)realloc(*negMas, ++sizes[1] * sizeof(int8_t));
			*(*negMas + sizes[1] - 1) = *(mas + i);
		}
		if (*(mas + i) == 0) {
			*zeroMas = (int8_t*)realloc(*zeroMas, ++sizes[2] * sizeof(int8_t));
			*(*zeroMas + sizes[2] - 1) = *(mas + i);
		}
		if (*(mas + i) > 0) {
			*posMas = (int8_t*)realloc(*posMas, ++sizes[3] * sizeof(int8_t));
			*(*posMas + sizes[3] - 1) = *(mas + i);
		}
	}

	return mas;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Init massive.\n");
	printf("2 - Print massive.\n");
	printf("3 - Distribute massive.\n");
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
	uint8_t sizes[4] = { 0 };
	int8_t* mas = NULL;
	int8_t* negMas = NULL;
	int8_t* zeroMas = NULL;
	int8_t* posMas = NULL;

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			if (mas) {
				free(mas);
			}

			mas = initMas(sizes[0] = inputValue("Input size of massive: "));

			break;

		case 2:
			printMas(mas, sizes[0]);
			break;

		case 3:
			distributeMas(mas, &negMas, &zeroMas, &posMas, sizes);

			if (negMas) {
				printf("Negative ");
				printMas(negMas, sizes[1]);
			}
			if (zeroMas) {
				printf("Zero ");
				printMas(zeroMas, sizes[2]);
			}
			if (posMas) {
				printf("Positive ");
				printMas(posMas, sizes[3]);
			}

			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}
		printf("Done. Press any key.");
		_getch();
	}

	free(negMas);
	free(zeroMas);
	free(posMas);

	return 0;
}