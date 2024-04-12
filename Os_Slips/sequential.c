#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

int disk[MAX_BLOCKS]; // Disk blocks

void initializeDisk(int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        disk[i] = rand() % 2; // Randomly allocate blocks
    }
}

void showBitVector(int n) {
    printf("Bit Vector: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

void showDirectory(int n) {
    printf("Directory:\n");
    printf("Block Number\tStatus\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%s\n", i, disk[i] ? "Allocated" : "Free");
    }
}

void deleteFile(int n) {
    int start, length;
    printf("Enter starting block number of file to delete: ");
    scanf("%d", &start);
    printf("Enter length of file to delete: ");
    scanf("%d", &length);

    if (start < 0 || start >= n || start + length > n) {
        printf("Invalid file range.\n");
        return;
    }

    for (int i = start; i < start + length; i++) {
        if (disk[i] == 0) {
            printf("Block %d is already free.\n", i);
        } else {
            disk[i] = 0;
            printf("Block %d freed.\n", i);
        }
    }
}

int main() {
    int n, choice;
    
    printf("Enter the number of blocks in disk: ");
    scanf("%d", &n);

    initializeDisk(n);
    
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Show Directory\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                showBitVector(n);
                break;
            case 2:
                showDirectory(n);
                break;
            case 3:
                deleteFile(n);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
    
    return 0;
}
