#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head, direction, total_head_movement = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the head movement direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Sort the requests
    qsort(requests, n, sizeof(int), compare);

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) {
            index = i;
            break;
        }
    }

    if (direction == 1) { // Moving right
        for (int i = index; i < n; i++) {
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        for (int i = index - 1; i >= 0; i--) {
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    } else { // Moving left
        for (int i = index - 1; i >= 0; i--) {
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        for (int i = index; i < n; i++) {
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("Total head movement is: %d\n", total_head_movement);

    return 0;
}
