#include <stdio.h>

#define PRODUCTS 4
#define CODE_LEN 4
#define NAME_LEN 50
#define CNIC_LEN 20
#define CART_CAP 100

int equalCode(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

void getCustomerInfo(char name[], char cnic[]) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Enter customer name: ");
    if (fgets(name, NAME_LEN, stdin) == NULL) {
        name[0] = '\0';
    }
    int i = 0;
    while (name[i] != '\0') i++;
    if (i > 0 && name[i-1] == '\n') name[i-1] = '\0';
    printf("Enter CNIC: ");
    if (fgets(cnic, CNIC_LEN, stdin) == NULL) {
        cnic[0] = '\0';
    }
    i = 0;
    while (cnic[i] != '\0') i++;
    if (i > 0 && cnic[i-1] == '\n') cnic[i-1] = '\0';
    printf("Customer recorded: %s, %s\n", name, cnic);
}

void displayInventory(char codes[][CODE_LEN], int qty[], int price[]) {
    printf("\nCode\tQuantity\tPrice\n");
    for (int i = 0; i < PRODUCTS; i++) {
        printf("%s\t%d\t\t%d\n", codes[i], qty[i], price[i]);
    }
}

int findProductIndex(char codes[][CODE_LEN], char code[]) {
    for (int i = 0; i < PRODUCTS; i++) {
        if (equalCode(codes[i], code)) return i;
    }
    return -1;
}

void addToCart(char codes[][CODE_LEN], int stock[], int price[], char cartCodes[][CODE_LEN], int cartQty[], int *cartCount) {
    char code[CODE_LEN];
    int q;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Enter product code (e.g. 001): ");
    if (fgets(code, CODE_LEN, stdin) == NULL) return;
    int i = 0;
    while (code[i] != '\0' && code[i] != '\n') i++;
    code[i] = '\0';
    int idx = findProductIndex(codes, code);
    if (idx == -1) {
        printf("Invalid product code.\n");
        return;
    }
    printf("Enter quantity to add to cart: ");
    if (scanf("%d", &q) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid quantity.\n");
        return;
    }
    if (q <= 0) {
        printf("Quantity must be positive.\n");
        return;
    }
    if (stock[idx] < q) {
        printf("Insufficient stock. Available: %d\n", stock[idx]);
        return;
    }
    int found = -1;
    for (int j = 0; j < *cartCount; j++) {
        if (equalCode(cartCodes[j], code)) {
            found = j;
            break;
        }
    }
    if (found == -1) {
        if (*cartCount >= CART_CAP) {
            printf("Cart is full.\n");
            return;
        }
        int pos = *cartCount;
        int k = 0;
        while (code[k] != '\0') {
            cartCodes[pos][k] = code[k];
            k++;
        }
        cartCodes[pos][k] = '\0';
        cartQty[pos] = q;
        (*cartCount)++;
    } else {
        cartQty[found] += q;
    }
    stock[idx] -= q;
    printf("Added %d of %s to cart.\n", q, code);
}

double calculateSubtotal(char codes[][CODE_LEN], int price[], char cartCodes[][CODE_LEN], int cartQty[], int cartCount) {
    double total = 0.0;
    for (int i = 0; i < cartCount; i++) {
        int idx = findProductIndex(codes, cartCodes[i]);
        if (idx != -1) {
            total += (double)price[idx] * cartQty[i];
        }
    }
    return total;
}

void displayBill(char codes[][CODE_LEN], int price[], char cartCodes[][CODE_LEN], int cartQty[], int cartCount) {
    if (cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }
    printf("\nInvoice Details:\n");
    printf("Code\tQty\tUnitPrice\tLineTotal\n");
    for (int i = 0; i < cartCount; i++) {
        int idx = findProductIndex(codes, cartCodes[i]);
        if (idx != -1) {
            int unit = price[idx];
            int q = cartQty[i];
            printf("%s\t%d\t%d\t\t%d\n", cartCodes[i], q, unit, unit * q);
        }
    }
    double subtotal = calculateSubtotal(codes, price, cartCodes, cartQty, cartCount);
    printf("Subtotal: %.2f\n", subtotal);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char promo[20];
    printf("Do you have a promo code? (enter code or press Enter to skip): ");
    if (fgets(promo, 20, stdin) == NULL) promo[0] = '\0';
    int i = 0;
    while (promo[i] != '\0' && promo[i] != '\n') i++;
    promo[i] = '\0';
    double discount = 0.0;
    if (i > 0) {
        char target[] = "Eid2025";
        int match = 1;
        int j = 0;
        while (target[j] != '\0' || promo[j] != '\0') {
            if (target[j] != promo[j]) { match = 0; break; }
            j++;
        }
        if (match) discount = 0.25 * subtotal;
    }
    double total = subtotal - discount;
    printf("Discount: %.2f\n", discount);
    printf("Total after discount: %.2f\n", total);
}

void showInvoice(char name[], char cnic[], char codes[][CODE_LEN], int price[], char cartCodes[][CODE_LEN], int cartQty[], int cartCount) {
    printf("\nCustomer: %s\nCNIC: %s\n", name, cnic);
    displayBill(codes, price, cartCodes, cartQty, cartCount);
}

int main() {
    char productCodes[PRODUCTS][CODE_LEN] = {"001","002","003","004"};
    int stock[PRODUCTS] = {50,10,20,8};
    int price[PRODUCTS] = {100,200,300,150};
    char customerName[NAME_LEN] = "";
    char customerCNIC[CNIC_LEN] = "";
    char cartCodes[CART_CAP][CODE_LEN];
    int cartQty[CART_CAP];
    int cartCount = 0;
    int choice;
    int running = 1;
    while (running) {
        printf("\nSupermarket System\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill (Checkout)\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input.\n");
            continue;
        }
        switch (choice) {
            case 1:
                getCustomerInfo(customerName, customerCNIC);
                break;
            case 2:
                displayInventory(productCodes, stock, price);
                break;
            case 3:
                addToCart(productCodes, stock, price, cartCodes, cartQty, &cartCount);
                break;
            case 4:
                displayBill(productCodes, price, cartCodes, cartQty, cartCount);
                break;
            case 5:
                showInvoice(customerName, customerCNIC, productCodes, price, cartCodes, cartQty, cartCount);
                break;
            case 6:
                printf("Exiting system.\n");
                running = 0;
                break;
            default:
                printf("Choose a valid option.\n");
        }
    }
    return 0;
}

