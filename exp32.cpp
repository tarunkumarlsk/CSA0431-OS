#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_REF_STR 25

int main() {
    int i, j, k, min, rs[MAX_REF_STR], m[MAX_FRAMES], count[MAX_FRAMES], flag[MAX_REF_STR], n, f, pf = 0, next = 1;
    
    // Input the length of the reference string
    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    // Input the reference string
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
        flag[i] = 0;
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++) {
        count[i] = 0;
        m[i] = -1;
    }

    printf("\nThe Page Replacement process is:\n");
    for (i = 0; i < n; i++) {
        // Check if the page is already in one of the frames
        for (j = 0; j < f; j++) {
            if (m[j] == rs[i]) {
                flag[i] = 1;
                count[j] = next;
                next++;
                break;
            }
        }

        // If the page was not found in any frame
        if (flag[i] == 0) {
            if (i < f) {
                // If there's space in the frames, just add the page
                m[i] = rs[i];
                count[i] = next;
                next++;
            } else {
                // Replace the least recently used page
                min = 0;
                for (j = 1; j < f; j++) {
                    if (count[min] > count[j])
                        min = j;
                }
                m[min] = rs[i];
                count[min] = next;
                next++;
            }
            pf++;
        }

        // Print the current state of frames
        for (j = 0; j < f; j++) {
            printf("%d\t", m[j]);
        }
        if (flag[i] == 0) {
            printf("PF No. %d", pf);
        }
        printf("\n");
    }

    printf("\nThe number of page faults using LRU are %d\n", pf);

    return 0;
}
