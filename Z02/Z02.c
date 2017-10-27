/*
Ќаписать функцию, котора€ получает указатель на динамический массив и его размер. ‘ункци€ должна удалить из 
массива все простые числа и вернуть указатель на новый динамический массив.
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

uint8_t* initMas(uint8_t size) {
	uint8_t* mas = (uint8_t*)calloc(size, sizeof(uint8_t));

	for (uint8_t i = 0; i < size; i++) {
		mas[i] = rand() % 10;
	}

	return mas;
}

uint8_t* printMas(uint8_t* mas, uint8_t size) {
	if (mas == NULL) {
		return NULL;
	}

	printf("Massive: ");
	for (uint8_t i = 0; i < size; i++) {
		printf("%3hhu", mas[i]);
	}
	printf("\n");

	return mas;
}

bool isSimple(uint8_t val) {
	if (val < 2) {
		return false;
	}

	for (uint8_t i = 2; i <= sqrt(val); i++) {
		if (val%i == 0) {
			return false;
		}
	}

	return true;
}

uint8_t* moveMas(uint8_t* mas, uint8_t end) {
	for (int8_t i = 0; i < end; i++) {
		*(mas + i) = *(mas + i + 1);
	}

	return mas;
}

uint8_t* simpleMas(uint8_t* mas, uint8_t* size) {
	for (uint8_t i = 0; i < *size; ) {
		if (isSimple(*(mas + i))) {
			moveMas(mas + i, *size - i - 1);
			mas = (uint8_t*)realloc(mas, --*size * sizeof(uint8_t));
		}
		else {
			i++;
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
	printf("3 - Dell all simple values from massive.\n");
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

	uint8_t size = 0;
	uint8_t ch = 0;
	uint8_t* mas = NULL;

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			if (mas) {
				free(mas);
			}

			mas = initMas(size = inputValue("Input size of massive: "));

			break;

		case 2:
			printMas(mas, size);
			break;

		case 3:
			mas = simpleMas(mas, &size);
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