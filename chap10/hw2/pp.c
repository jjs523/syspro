#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) return -1;

    struct node *temp = *head;
    int deleteData = temp->data;

    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return deleteData;
}

void print_queue(struct node *head) {
    printf("Print queue\n");
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int data;

    while (scanf("%d", &data) == 1) {
        addq(&head, &tail, data);
    }
    
    while (getchar() != '\n');

    print_queue(head);

    return 0;
}
