#include <stdio.h>

#define MAX_BLOCKS 100

int memory[MAX_BLOCKS];
int processSizes[MAX_BLOCKS]; // Array to store the size of each allocated process

// Function prototypes
void initializeMemory(int size);
int bestFit(int size);
void deallocateMemory(int blockIndex);
void displayMemoryStatus();

int main() {
    int memorySize, choice, processSize, blockIndex;

    printf("Enter the total size of memory: ");
    scanf("%d", &memorySize);

    initializeMemory(memorySize);

    while (1) {
        printf("\n1. Allocate Memory\n2. Deallocate Memory\n3. Display Memory Status\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the process: ");
                scanf("%d", &processSize);
                blockIndex = bestFit(processSize);
                if (blockIndex != -1) {
                    printf("Memory allocated successfully at block %d\n", blockIndex);
                    processSizes[blockIndex] = processSize; // Store the size of the allocated process
                    displayMemoryStatus();
                } else {
                    printf("Memory allocation failed. No suitable block found.\n");
                }
                break;
            case 2:
                printf("Enter the block index to deallocate: ");
                scanf("%d", &blockIndex);
                if (blockIndex >= 0 && blockIndex < MAX_BLOCKS && processSizes[blockIndex] > 0) {
                    deallocateMemory(blockIndex);
                    printf("Memory deallocated successfully from block %d\n", blockIndex);
                    displayMemoryStatus();
                } else {
                    printf("Invalid block index or the block is already free.\n");
                }
                break;
            case 3:
                displayMemoryStatus();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void initializeMemory(int size) {
    int blockSize = size / MAX_BLOCKS;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memory[i] = blockSize;
        processSizes[i] = 0; // Initialize process sizes to 0 indicating no allocation
    }
}

int bestFit(int size) {
    int minBlockSize = memory[MAX_BLOCKS - 1] + 1;
    int blockIndex = -1;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i] >= size && memory[i] < minBlockSize) {
            minBlockSize = memory[i];
            blockIndex = i;
        }
    }

    if (blockIndex != -1) {
        memory[blockIndex] -= size;
    }

    return blockIndex;
}

void deallocateMemory(int blockIndex) {
    memory[blockIndex] += processSizes[blockIndex];
    processSizes[blockIndex] = 0; // Reset the process size for the deallocated block
}

void displayMemoryStatus() {
    printf("Memory Status:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Block %d: %d\n", i, memory[i]);
    }
}
