#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Node structure for linked list representing allocated blocks
struct Node {
    int blockNumber;
    struct Node* next;
};

// Function prototypes
void showBitVector(int bitVector[], int n);
void createNewFile(int bitVector[], struct Node* directory[], int* numFiles, int n);
void showDirectory(struct Node* directory[], int numFiles);

int main() {
    int n, choice, numFiles = 0;
    int bitVector[MAX_BLOCKS] = {0}; // 0 represents false
    struct Node* directory[MAX_FILES] = {NULL};
    
    printf("Enter the number of blocks on the disk: ");
    scanf("%d", &n);

    
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                showBitVector(bitVector, n);
                break;
            case 2:
                createNewFile(bitVector, directory, &numFiles, n);
                break;
            case 3:
                showDirectory(directory, numFiles);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
        
    } while(choice != 4);
    
    return 0;
}

// Function to display the bit vector
void showBitVector(int bitVector[], int n) {
    int i;
    printf("Bit Vector:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", bitVector[i]);
    }
    printf("\n");
}

// Function to create a new file at the specified block
void createNewFile(int bitVector[], struct Node* directory[], int* numFiles, int n) {
    int block;
    struct Node* newNode = NULL;
    
    printf("Enter the block number where you want to create the file (0 to %d): ", n - 1);
    scanf("%d", &block);
    
    if (block < 0 || block >= n) {
        printf("Invalid block number!\n");
        return;
    }
    
    if (bitVector[block]) {
        printf("Block %d is already allocated. Cannot create file.\n", block);
        return;
    }
    
    // Add the allocated block to directory
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->blockNumber = block;
    newNode->next = directory[*numFiles];
    directory[*numFiles] = newNode;
    
    bitVector[block] = 1; // 1 represents true
    (*numFiles)++;
    
    printf("New file created successfully at block %d.\n", block);
}

// Function to display the directory
void showDirectory(struct Node* directory[], int numFiles) {
    int i;
    printf("Directory:\n");
    for (i = 0; i < numFiles; i++) {
        printf("File %d: ", i + 1);
        struct Node* temp = directory[i];
        while (temp != NULL) {
            printf("%d ", temp->blockNumber);
            temp = temp->next;
        }
        printf("\n");
    }
}
