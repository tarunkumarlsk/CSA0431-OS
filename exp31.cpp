#include <stdio.h>

int main() {
    int i, j, k, f, pf = 0, count = 0, rs[25], m[10], n;
    
    // Input the length of the reference string
    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    // Input the reference string
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rs[i]);

    // Input the number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++)
        m[i] = -1;

    printf("\nThe Page Replacement Process is:\n");
    for (i = 0; i < n; i++) {
        // Check if page is already in one of the frames
        for (k = 0; k < f; k++) {
            if (m[k] == rs[i]) 
                break;
        }

        // If page not found in any frame, replace it
        if (k == f) {
            m[count++] = rs[i];
            pf++;
        }

        // Print current state of frames
        for (j = 0; j < f; j++)
            printf("\t%d", m[j]);

        // Print page fault number
        if (k == f)
            printf("\tPF No. %d", pf);

        printf("\n");

        // Circular replacement
        if (count == f)
            count = 0;
    }

    printf("\nThe number of Page Faults using FIFO are %d\n", pf);

    return 0;
}
