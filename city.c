#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

// Структура для представления информации о городе
typedef struct City {
    char name[50];
    int population;
    struct City* next;
} City;

// Хэш-таблица для хранения городов
City* hashtable[SIZE];

// Функция для вычисления хэша на основе имени города
int hashFunc(char* name) {
    int sum = 0;
    for (int i = 0; i < strlen(name); i++) {
        sum += name[i];
    }
    return sum % SIZE;
}

// Функция для добавления информации о городе в хэш-таблицу
void addCity(char* name, int population) {
    City* newCity = (City*)malloc(sizeof(City));
    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->next = NULL;

    int hashValue = hashFunc(name);

    if (hashtable[hashValue] == NULL) {
        hashtable[hashValue] = newCity;
    } else {
        City* current = hashtable[hashValue];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCity;
    }
}

// Функция для удаления информации о городе из хэш-таблицы
void removeCity(char* name) {
    int hashValue = hashFunc(name);

    if (hashtable[hashValue] == NULL) {
        printf("Город %s не найден\n", name);
    } else {
        City* current = hashtable[hashValue];
        City* prev = NULL;

        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                if (prev == NULL) {
                    hashtable[hashValue] = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                printf("Информация о городе %s удалена\n", name);
                return;
            }

            prev = current;
            current = current->next;
        }

        printf("Город %s не найден\n", name);
    }
}

// Функция для вывода списка городов
void listCities() {
    for (int i = 0; i < SIZE; i++) {
        City* current = hashtable[i];

        while (current != NULL) {
            printf("Город: %s, Население: %d\n", current->name, current->population);
            current = current->next;
        }
    }
}

int main() {
    int choice;
    char name[50];
    int population;

    while (1) {
        printf("\n1. Добавить информацию о городе\n");
        printf("2. Удалить информацию о городе\n");
        printf("3. Вывести список городов\n");
        printf("4. Выход\n");
        printf("Введите выбор (1-4): \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите имя города: \n");
                scanf("%s", name);
                printf("Введите население города: \n");
                scanf("%d", &population);
                addCity(name, population);
                break;
            case 2:
                printf("Введите имя города: \n");
                scanf("%s", name);
                removeCity(name);
                break;
            case 3:
                listCities();
                break;
            case 4:
                exit(0);
		
        }
    }

    return 0;
}
