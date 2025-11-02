#include <stdio.h>

#define ROWS 3
#define COLS 3

void updateSector(int grid[ROWS][COLS]) {
    int r, c, flag, value;
    printf("Enter sector coordinates (row and column): ");
    scanf("%d%d", &r, &c);
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        printf("Invalid coordinates.\n");
        return;
    }
    printf("Enter flag to modify (0=Power, 1=Overload, 2=Maintenance): ");
    scanf("%d", &flag);
    if (flag < 0 || flag > 2) {
        printf("Invalid flag.\n");
        return;
    }
    printf("Enter value (1=set, 0=clear): ");
    scanf("%d", &value);
    if (value == 1)
        grid[r][c] |= (1 << flag);
    else
        grid[r][c] &= ~(1 << flag);
    printf("Sector updated.\n");
}

void querySector(int grid[ROWS][COLS]) {
    int r, c;
    printf("Enter sector coordinates to query: ");
    scanf("%d%d", &r, &c);
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        printf("Invalid coordinates.\n");
        return;
    }
    int val = grid[r][c];
    printf("Sector [%d][%d] Status:\n", r, c);
    printf("Power: %s\n", (val & 1) ? "ON" : "OFF");
    printf("Overload: %s\n", (val & 2) ? "Yes" : "No");
    printf("Maintenance Required: %s\n", (val & 4) ? "Yes" : "No");
}

void diagnostic(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & 2) overloadCount++;
            if (grid[i][j] & 4) maintenanceCount++;
        }
    }
    printf("Total overloaded sectors: %d\n", overloadCount);
    printf("Total maintenance required: %d\n", maintenanceCount);
}

int main() {
    int grid[ROWS][COLS] = {0};
    int choice;
    while (1) {
        printf("\nIESCO Power Grid System\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                updateSector(grid);
                break;
            case 2:
                querySector(grid);
                break;
            case 3:
                diagnostic(grid);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}

