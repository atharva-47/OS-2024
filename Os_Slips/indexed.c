#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

// Function prototypes
void showBitVector(int *bitVector, int n);
void createNewFile(int *bitVector, int n);
void showDirectory(int *bitVector, int n);
void deleteFile(int *bitVector, int n);

int main() {
    int n, choice;
    int bitVector[MAX_BLOCKS] = {0}; // 0 indicates free block, 1 indicates allocated block

    printf("Enter the number of blocks in disk: ");
    scanf("%d", &n);

    srand(time(NULL)); // Seed random number generator

    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                showBitVector(bitVector, n);
                break;
            case 2:
                createNewFile(bitVector, n);
                break;
            case 3:
                showDirectory(bitVector, n);
                break;
            case 4:
                deleteFile(bitVector, n);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);

    return 0;
}

// Function to display the bit vector representing the disk
void showBitVector(int *bitVector, int n) {
    printf("Bit Vector:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", bitVector[i]);
    }
    printf("\n");
}

// Function to create a new file
void createNewFile(int *bitVector, int n) {
    int index;
    for(;;) {
        index = rand() % n;
        if(bitVector[index] == 0) {
            bitVector[index] = 1;
            printf("File created at block %d\n", index);
            break;
        }
    }
}

// Function to display the directory
void showDirectory(int *bitVector, int n) {
    printf("Directory:\n");
    printf("Index\tStatus\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\n", i, bitVector[i] == 1 ? "Allocated" : "Free");
    }
}

// Function to delete a file
void deleteFile(int *bitVector, int n) {
    int index;
    printf("Enter the block number to delete the file: ");
    scanf("%d", &index);
    if(index < 0 || index >= n) {
        printf("Invalid block number!\n");
        return;
    }
    if(bitVector[index] == 1) {
        bitVector[index] = 0;
        printf("File at block %d deleted successfully.\n", index);
    } else {
        printf("No file found at block %d.\n", index);
    }
}
