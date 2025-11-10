#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    int n;
    printf("\nEnter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("\nEnter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("\nFork failed...!");
        return 1;
    } else if (pid == 0) {
        printf("\nChild process (PID: %d) sorting using Bubble Sort...\n", getpid());
        bubbleSort(arr, n);
        printf("\nChild process sorted array (Bubble Sort):");
        for (int i = 0; i < n; i++)
            printf("\t%d", arr[i]);
        printf("\n");
        exit(0);
    } else {
        sleep(5); // Wait for child process to finish
        printf("\nParent process (PID: %d) sorting using Selection Sort...\n", getpid());
        selectionSort(arr, n);
        printf("\nParent process sorted array (Selection Sort):");
        for (int i = 0; i < n; i++)
            printf("\t%d", arr[i]);
        printf("\n");
    }

    return 0;
}