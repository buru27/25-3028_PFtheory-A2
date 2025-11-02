#include <stdio.h>

#define MAX_BOOKS 100
#define TITLE_LEN 50

int findBookIndex(int isbns[], int count, int isbn) {
    for (int i = 0; i < count; i++) {
        if (isbns[i] == isbn) return i;
    }
    return -1;
}

void addNewBook(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Inventory full. Cannot add more books.\n");
        return;
    }

    int isbn;
    printf("Enter ISBN (integer): ");
    if (scanf("%d", &isbn) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (findBookIndex(isbns, *count, isbn) != -1) {
        printf("A book with this ISBN already exists.\n");
        return;
    }

    while (getchar() != '\n');

    char title[TITLE_LEN];
    printf("Enter Title: ");
    if (fgets(title, TITLE_LEN, stdin) == NULL) {
        printf("Input error.\n");
        return;
    }
    int tlen = 0;
    while (title[tlen] != '\0') tlen++;
    if (tlen > 0 && title[tlen-1] == '\n') title[tlen-1] = '\0';

    float price;
    printf("Enter Price: ");
    if (scanf("%f", &price) != 1) {
        while (getchar() != '\n');
        printf("Invalid price.\n");
        return;
    }

    int qty;
    printf("Enter Quantity: ");
    if (scanf("%d", &qty) != 1) {
        while (getchar() != '\n');
        printf("Invalid quantity.\n");
        return;
    }

    int idx = *count;
    isbns[idx] = isbn;
    for (int i = 0; i < TITLE_LEN; i++) {
        titles[idx][i] = title[i];
        if (title[i] == '\0') break;
    }
    prices[idx] = price;
    quantities[idx] = qty;
    (*count)++;
    printf("Book added successfully. Total books: %d\n", *count);
}

void processSale(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int *count) {
    if (*count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    int isbn;
    printf("Enter ISBN to sell: ");
    if (scanf("%d", &isbn) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    int idx = findBookIndex(isbns, *count, isbn);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    int sold;
    printf("Enter number of copies sold: ");
    if (scanf("%d", &sold) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (sold <= 0) {
        printf("Enter a positive number of copies.\n");
        return;
    }

    if (quantities[idx] < sold) {
        printf("Insufficient stock. Available: %d\n", quantities[idx]);
        return;
    }

    quantities[idx] -= sold;
    printf("Sale processed. Remaining quantity of \"%s\": %d\n", titles[idx], quantities[idx]);
}

void lowStockReport(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int count) {
    int found = 0;
    printf("Low Stock Report (quantity < 5):\n");
    printf("ISBN\tTitle\t\tPrice\tQuantity\n");
    for (int i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            found = 1;
            printf("%d\t%s\t\t%.2f\t%d\n", isbns[i], titles[i], prices[i], quantities[i]);
        }
    }
    if (!found) {
        printf("No books with quantity below 5.\n");
    }
}

int main() {
    int isbns[MAX_BOOKS] = {0};
    char titles[MAX_BOOKS][TITLE_LEN];
    float prices[MAX_BOOKS] = {0.0f};
    int quantities[MAX_BOOKS] = {0};
    int bookCount = 0;
    int choice = 0;

    while (1) {
        printf("\nLiberty Books - Branch Inventory\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid choice.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addNewBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, &bookCount);
                break;
            case 3:
                lowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid option. Choose 1-4.\n");
        }
    }
    return 0;
}

