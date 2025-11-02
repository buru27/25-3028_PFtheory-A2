#include <stdio.h>
#define MAX 100

void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize - 1) {
        printf("Stack overflow.\n");
        return;
    }
    int val;
    printf("Enter value to push: ");
    scanf("%d", &val);
    stack[++(*top)] = val;
    printf("Value pushed.\n");
}

void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack underflow.\n");
        return;
    }
    printf("Popped value: %d\n", stack[(*top)--]);
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack empty.\n");
        return;
    }
    printf("Top element: %d\n", stack[top]);
}

void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack empty.\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

int main() {
    int stack[MAX];
    int top = -1;
    int choice;
    while (1) {
        printf("\nStack Menu\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                push(stack, &top, MAX);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}

