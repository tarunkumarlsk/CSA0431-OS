#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

int main() {
    int no_of_frames, no_of_pages, frames[MAX_FRAMES], pages[MAX_PAGES];
    int temp[MAX_FRAMES], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;

    // Input the number of frames
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Input the number of pages
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    // Input the page reference string
    printf("Enter page reference string: ");
    for (i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames to -1 (indicating empty)
    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    // Page replacement algorithm
    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        // Check if page is already in one of the frames
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page is not found in the frames
        if (flag1 == 0) {
            // Check if there's an empty frame
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty frame is found
        if (flag2 == 0) {
            flag3 = 0;

            // Find the future use of each frame's page
            for (j = 0; j < no_of_frames; ++j) {
                temp[j] = -1;
                for (k = i + 1; k < no_of_pages; ++k) {
                    if (frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find the frame to be replaced
            for (j = 0; j < no_of_frames; ++j) {
                if (temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            // If all frames have future use
            if (flag3 == 0) {
                max = temp[0];
                pos = 0;
                for (j = 1; j < no_of_frames; ++j) {
                    if (temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            faults++;
        }

        // Print current state of frames
        printf("\n");
        for (j = 0; j < no_of_frames; ++j) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}
