#include <stdio.h>

void reverseString(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void toggleBits(char *c) {
    *c ^= (1 << 1);
    *c ^= (1 << 4);
}

void encodeMessage(char msg[]) {
    reverseString(msg);
    int i = 0;
    while (msg[i] != '\0') {
        toggleBits(&msg[i]);
        i++;
    }
}

void decodeMessage(char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        toggleBits(&msg[i]);
        i++;
    }
    reverseString(msg);
}

int main() {
    char message[200];
    int choice;
    while (1) {
        printf("\nTCS Secure Messaging System\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (choice == 1) {
            printf("Enter message to encode: ");
            fgets(message, 200, stdin);
            int i = 0;
            while (message[i] != '\0' && message[i] != '\n') i++;
            message[i] = '\0';
            encodeMessage(message);
            printf("Encoded Message: %s\n", message);
        } else if (choice == 2) {
            printf("Enter message to decode: ");
            fgets(message, 200, stdin);
            int i = 0;
            while (message[i] != '\0' && message[i] != '\n') i++;
            message[i] = '\0';
            decodeMessage(message);
            printf("Decoded Message: %s\n", message);
        } else if (choice == 3) {
            printf("Exiting system.\n");
            return 0;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

