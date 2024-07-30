#include <stdio.h>
#include <stdlib.h>

int main() {
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;

    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position\n");
    scanf("%d", &initial);

    printf("Enter total disk size\n");
    scanf("%d", &size);

    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);

    // Sort the request array
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) { // Move towards high end
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(size - RQ[i - 1] - 1);
        TotalHeadMovement += abs(size - 1 - 0);
        initial = 0;
        for (i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else { // Move towards low end
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(RQ[i + 1] - 0);
        TotalHeadMovement += abs(size - 1 - 0);
        initial = size - 1;
        for (i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d\n", TotalHeadMovement);

    return 0;
}
