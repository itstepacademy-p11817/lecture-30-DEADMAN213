/*
Написать следующие функции для работы с динамическим массивом:
* Функция инициализации динамического массива+
* Функция печати динамического массива+
* Функция удаления динамического массива+
* Функция добавления элемента в конец массива
* Функция вставки элемента по указанному индексу
* Функция удаления элемента по указанному индексу
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>
#include <conio.h>

uint8_t inputValue(const char* mes) {
	uint8_t val = 0;
	printf(mes);
	scanf("%hhu", &val);

	return val;
}

uint8_t* initMas(uint8_t size) {
	uint8_t* mas = (uint8_t*)calloc(size, sizeof(uint8_t));

	for (uint8_t i = 0; i < size; i++) {
		mas[i] = rand() % 100;
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

uint8_t* dellMas(uint8_t* mas) {
	free(mas);

	return NULL;
}

uint8_t* expandMas(uint8_t* mas, uint8_t* size, uint8_t pos) {
	mas = realloc(mas, ++*size * sizeof(uint8_t));
	
	for (uint8_t i = *size - 1; i > pos - 1; i--) {
		mas[i] = mas[i - 1];
	}

	mas[pos - 1] = rand() % 100;

	return mas;
}

uint8_t* compressMas(uint8_t* mas, uint8_t* size, uint8_t pos) {
	for (uint8_t i = pos - 1; i < *size - 1; i++) {
		mas[i] = mas[i + 1];
	}

	return (uint8_t*)realloc(mas, --*size * sizeof(uint8_t));
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Init massive.\n");
	printf("2 - Print massive.\n");
	printf("3 - Dell massive.\n");
	printf("4 - Add element at the end.\n");
	printf("5 - Insert element in position.\n");
	printf("6 - Dell element in position.\n");
	printf("7 - Exit.\n");
	printf("Your choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	uint8_t size = 0;
	uint8_t ch = 0;
	uint8_t* mas = NULL;
	
	srand(time(NULL));

	while ((ch = menu()) != 7) {
		switch (ch) {
		case 1:
			mas = initMas(size = inputValue("Input size of massive: "));
			break;

		case 2:
			printMas(mas, size);
			break;

		case 3:
			mas = dellMas(mas);
			break;

		case 4:
			mas = expandMas(mas, &size, size + 1);
			break;

		case 5:
			mas = expandMas(mas, &size, inputValue("Input number of position: "));
			break;

		case 6:
			mas = compressMas(mas, &size, inputValue("Input number of position: "));
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}
		printf("Done. Press any key.");
		_getch();
	}

	return 0;
}