#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

int main() {
    int disk[MAX_BLOCKS] = {0};  // Initialize all blocks to 0 (free)
    int index[MAX_BLOCKS];
    int i, j, n, st, len, k, ind, count, choice;

    while (1) {
        // Input the index block
        printf("Enter the index block: ");
        scanf("%d", &ind);

        // Check if the index block is already allocated
        if (ind < 0 || ind >= MAX_BLOCKS || disk[ind] == 1) {
            printf("Index %d is already allocated or invalid.\n", ind);
            continue;
        }

        // Input the number of blocks needed
        printf("Enter number of blocks needed for the index %d on the disk: \n", ind);
        scanf("%d", &n);

        // Input the blocks to allocate
        count = 0;
        printf("Enter the blocks: \n");
        for (i = 0; i < n; i++) {
            scanf("%d", &index[i]);
            if (index[i] < 0 || index[i] >= MAX_BLOCKS) {
                printf("Block %d is out of range.\n", index[i]);
                continue;
            }
            if (disk[index[i]] == 0) {
                count++;
            }
        }

        // Allocate the blocks if enough free blocks are found
        if (count == n) {
            for (j = 0; j < n; j++) {
                disk[index[j]] = 1;
            }
            printf("File allocated successfully.\n");
            printf("File Indexed:\n");
            for (k = 0; k < n; k++) {
                printf("%d-------->%d : %d\n", ind, index[k], disk[index[k]]);
            }
        } else {
            printf("Not enough contiguous free blocks. Please try again.\n");
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
