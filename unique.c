#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления узла бинарного дерева
struct Node {
    char *word; // слово
    int count; // частота повторения
    struct Node *left;
    struct Node *right;
};

// Функция для создания нового узла
struct Node* createNode(char *word) {
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->word = (char*) malloc(strlen(word) + 1);
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для вставки узла в бинарное дерево
struct Node* insert(struct Node* root, char *word) {
    // Если дерево пустое, создаем новый узел и возвращаем его
    if (root == NULL)
        return createNode(word);

    // Если слово уже присутствует в дереве, увеличиваем его частоту повторения
    if (strcmp(word, root->word) == 0) {
        root->count++;
    }
    // Если слово меньше текущего узла, проходим влево
    else if (strcmp(word, root->word) < 0) {
        root->left = insert(root->left, word);
    }
    // Если слово больше текущего узла, проходим вправо
    else {
        root->right = insert(root->right, word);
    }
    return root;
}

// Функция для обхода дерева в порядке возрастания
void inorder(struct Node* root, int sort) {
    if (root != NULL) {
        if (sort == 1) // по возрастанию
            inorder(root->left, sort);

        printf("%s: %d\n", root->word, root->count);

        if (sort == -1) // по убыванию
            inorder(root->left, sort);

        inorder(root->right, sort);
    }
}

// Функция для освобождения памяти, выделенной для узлов дерева
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->word);
        free(root);
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <file> [-o ASC|DESC]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s", fileName);
        return EXIT_FAILURE;
    }

    int sort = 1; // по умолчанию сортировка по возрастанию
    if (argc == 3 && strcmp(argv[2], "-o") == 0) {
        if (strcmp(argv[3], "DESC") == 0)
            sort = -1; // сортировка по убыванию
    }

    struct Node *root = NULL;
    char word[100];
    
    // Читаем слова из файла, вставляем их в бинарное дерево
    
    while (fscanf(file, "%s", word) != EOF) {
        root = insert(root, word);
    }
    
    inorder(root, sort);
    freeTree(root);

    fclose(file);
    return 0;
}
   
