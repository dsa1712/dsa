
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to calculate absolute difference
int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// Function to swap values
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort array in ascending order
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
}


// SSTF Algorithm
void sstf(int requests[], int n, int head) {
    int total_seek = 0, current = head;
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int diff = abs_diff(current, requests[j]);
                if (diff < min) {
                    min = diff;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total_seek += abs_diff(current, requests[index]);
        current = requests[index];
    }

    printf("\nSSTF:\nTotal Seek Time: %d\nAverage Seek Time: %.2f\n", total_seek, (float)total_seek / n);
}



// SCAN Algorithm
void scan(int requests[], int n, int head, int max_cylinder) {
    int total_seek = 0;
    int sorted[MAX];
    for (int i = 0; i < n; i++)
        sorted[i] = requests[i];

    sort(sorted, n);

    int i;
    for (i = 0; i < n; i++)
        if (sorted[i] >= head)
            break;

    int current = head;

    // Move towards higher requests
    for (int j = i; j < n; j++) {
        total_seek += abs_diff(current, sorted[j]);
        current = sorted[j];
    }

    // Move to end of disk
    total_seek += abs_diff(current, max_cylinder);
    current = max_cylinder;

    // Move back to smaller requests
    for (int j = i - 1; j >= 0; j--) {
        total_seek += abs_diff(current, sorted[j]);
        current = sorted[j];
    }

    printf("\nSCAN:\nTotal Seek Time: %d\nAverage Seek Time: %.2f\n", total_seek, (float)total_seek / n);
}



// C-LOOK Algorithm
void c_look(int requests[], int n, int head) {
    int total_seek = 0;
    int sorted[MAX];
    for (int i = 0; i < n; i++)
        sorted[i] = requests[i];

    sort(sorted, n);

    int i;
    for (i = 0; i < n; i++)
        if (sorted[i] >= head)
            break;

    int current = head;

    // Move towards higher requests
    for (int j = i; j < n; j++) {
        total_seek += abs_diff(current, sorted[j]);
        current = sorted[j];
    }

    // Jump to lowest request (no seek time counted)
    if (i > 0) {
        total_seek += abs_diff(current, sorted[0]);
        current = sorted[0];
    }

    // Continue from lowest to just before starting point
    for (int j = 0; j < i; j++) {
        total_seek += abs_diff(current, sorted[j]);
        current = sorted[j];
    }

    printf("\nC-LOOK:\nTotal Seek Time: %d\nAverage Seek Time: %.2f\n", total_seek, (float)total_seek / n);
}

int main() {
    int n, head, choice, max_cylinder;
    int requests[MAX];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    do {
        printf("\nChoose Disk Scheduling Algorithm:\n");
        printf("1. SSTF\n2. SCAN\n3. C-LOOK\n4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(requests, n, head);
                break;
            case 2:
                printf("Enter maximum cylinder number: ");
                scanf("%d", &max_cylinder);
                scan(requests, n, head, max_cylinder);
                break;
            case 3:
                c_look(requests, n, head);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}