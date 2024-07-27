#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

int main() {
    int disk[MAX_BLOCKS];
    int start, length, i, j, k, choice;
    int free_blocks, allocated;

    // Initialize the disk blocks to 0 (free)
    for (i = 0; i < MAX_BLOCKS; i++) {
        disk[i] = 0;
    }

    while (1) {
        free_blocks = 0;
        printf("Enter starting block and length of file: ");
        scanf("%d%d", &start, &length);

        // Check if the requested blocks are free
        for (k = start; k < (start + length); k++) {
            if (disk[k] == 0) {
                free_blocks++;
            }
        }

        // If all requested blocks are free, allocate the file
        if (length == free_blocks) {
            for (j = start; j < (start + length); j++) {
                if (disk[j] == 0) {
                    disk[j] = 1;  // Mark the block as allocated
                }
                printf("Block %d: %d\n", j, disk[j]);
            }
            printf("The file is allocated to disk.\n");
        } else {
            printf("The file is not allocated (not enough contiguous free blocks).\n");
        }

        // Ask if the user wants to enter more files
        printf("Do you want to enter more files? (Yes - 1 / No - 0): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }
    }

    return 0;
}
