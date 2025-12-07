#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) return -1;
    struct node *temp = *top;
    int popData = temp->data;
    *top = temp->next;
    free(temp);
    return popData;
}

void print_stack(struct node *top) {
    printf("Print stack\n");
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *top = NULL;
    int data;

    while (scanf("%d", &data) == 1) {
        push(&top, data);
    }

    while (getchar() != '\n');

    print_stack(top);

    return 0;
}
