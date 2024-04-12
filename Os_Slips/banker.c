#include <stdio.h>

#define MAX 10

int allocation[MAX][MAX];
int max[MAX][MAX];
int need[MAX][MAX];
int available[MAX];
int num_processes;
int num_resources;

int isSafeState() {
    int work[MAX];
    int finish[MAX] = {0};
    int safeSequence[MAX];
    int count = 0;

    // Initialize work to available
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safeSequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0; // System is not in a safe state
        }
    }

    // System is in a safe state, display the safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

void acceptAvailable() {
    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }
}

void displayAllocationMax() {
    printf("Allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Max matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

void displayNeed() {
    printf("Need matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() {
    printf("Available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter max matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Accept Available\n");
        printf("2. Display Allocation, Max\n");
        printf("3. Display the contents of need matrix\n");
        printf("4. Display Available\n");
        printf("5. Check Safe State\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                acceptAvailable();
                break;
            case 2:
                displayAllocationMax();
                break;
            case 3:
                displayNeed();
                break;
            case 4:
                displayAvailable();
                break;
            case 5:
                if (isSafeState()) {
                    printf("System is in a safe state.\n");
                } else {
                    printf("System is not in a safe state.\n");
                }
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
