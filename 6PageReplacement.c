#include <stdio.h>
#define MAX 100
#define FRAME_SIZE 3

// Global variables
int pages[MAX];         // Page reference string
int frames[FRAME_SIZE]; // Memory frames
int n;                  // Number of pages

// Initialize frames to -1 (empty)
void initializeFrames() {
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;
    }
}

// FIFO Page Replacement
void fifo() {
    int i, j, k = 0, page_faults = 0, hit;
    initializeFrames();

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            frames[k] = pages[i];
            k = (k + 1) % FRAME_SIZE;
            page_faults++;
        }
    }

    printf("Total Page Faults (FIFO): %d\n\n", page_faults);
}

// LRU Page Replacement
void lru() {
    int recent[FRAME_SIZE];
    int i, j, page_faults = 0, time = 0, hit;

    initializeFrames();
    for (i = 0; i < FRAME_SIZE; i++)
        recent[i] = 0;

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                recent[j] = time++;
                break;
            }
        }
        if (!hit) {
            int lru_index = 0;
            for (j = 1; j < FRAME_SIZE; j++) {
                if (recent[j] < recent[lru_index])
                    lru_index = j;
            }
            frames[lru_index] = pages[i];
            recent[lru_index] = time++;
            page_faults++;
        }
    }

    printf("Total Page Faults (LRU): %d\n\n", page_faults);
}

// Optimal Page Replacement
void optimal() {
    int i, j, k, page_faults = 0, hit;
    initializeFrames();

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int farthest = -1, index = -1;
            for (j = 0; j < FRAME_SIZE; j++) {
                int found = 0;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    index = j;
                    break;
                }
            }
            if (index == -1) index = 0;
            frames[index] = pages[i];
            page_faults++;
        }
    }

    printf("Total Page Faults (Optimal): %d\n\n", page_faults);
}

// Main Function with Menu Loop
int main() {
    int choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Menu loop
    do {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo();
                break;
            case 2:
                lru();
                break;
            case 3:
                optimal();
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