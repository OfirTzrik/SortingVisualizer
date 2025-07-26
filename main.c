#include <raylib.h>
#include <time.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void bubbleSort(int *array, int len);
void swap(int *x, int *y);
void printArray(int *array, int len);
void intToString(int num, char *str);
void drawArray(int *array, int len);
void fillArray(int *array, int len);
void quickSort(int *low, int *high);
int* partition(int *low, int *high);

#define getArrayLen(array) ((sizeof(array)) / (sizeof(array[0])))

int main(void) {
    /* Initialization */
    InitWindow(800, 600, "Sorting Visualizer");
    if(!IsWindowReady())
        return -1; /* Window failed to initialize */
    GuiLoadStyle("amber/style_amber.rgs");
    SetTargetFPS(60);
    srand(time(NULL));

    float currentValue = 1;
    int array[15];
    fillArray(array, getArrayLen(array));

    while(!WindowShouldClose()) {
        BeginDrawing();

        /* Content start */
        ClearBackground((Color){70, 70, 70, 255});
        DrawFPS(5, 5);
        
        GuiSlider((Rectangle){64, 32, 128, 16}, "Min: 1", "Max: 5", &currentValue, 1, 5);

        /* Draw the array before and after sorting */
        drawArray(array, getArrayLen(array));
        if(IsKeyPressed(KEY_SPACE)) {
            bubbleSort(array, getArrayLen(array));
        } else if(IsKeyPressed(KEY_ENTER)) {
            quickSort(array, array + getArrayLen(array) - 1);
        }

        /* Content end  */

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/* Perform bubble sort using pointers instead of indexing */
void bubbleSort(int *array, int len) {
    for(int i = 0; i < len; i++) {
        int *ptr = array;
        for(int j = 0; j < len - i - 1; j++, ptr++) {
            if(*ptr > *(ptr + 1))
                swap(ptr, ptr + 1);
        }
    }
}

/* Perform quick sort using pointers instead of indexing */
void quickSort(int *low, int *high) {
    if(low >= high)
        return;
    int *pivot = partition(low, high);
    quickSort(low, pivot - 1); /* Left partition */
    quickSort(pivot + 1, high); /* Right partition */
}

/* Partition the array based on the pivot
Depending on where the pivot ends up:
- On its left, numbers that are smaller 
- On its right, numbers that are larger */
int* partition(int *low, int *high) {
    /* Take the middle number as the pivot and put it at the end */
    swap(low + (high - low) / 2, high);
    int *pivot = high;
    int *largerFromLeft = low;
    int *smallerFromRight = high - 1;

    do {
        /* Look for the first larger number than the pivot from the left */
        while(*largerFromLeft < *pivot)
            largerFromLeft++;
        /* Look for the first smaller number than the pivot from the right */
        while(*smallerFromRight > *pivot)
            smallerFromRight--;

        /* Left pointer crossed the right pointer, stop */
        if(largerFromLeft > smallerFromRight)
            break;

        swap(largerFromLeft, smallerFromRight);
        /* Move so the next search starts beyond them */
        largerFromLeft++;
        smallerFromRight--;
    } while(true);
    swap(largerFromLeft, pivot); /* Place pivot at its correct spot */
    
    /* Return the spot where the pivot sits after the swap */
    return largerFromLeft;
}

/* Helper functions */

/* Swap two array items */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Print all numbers in the array */
void printArray(int *array, int len) {
    for(int i = 0; i < len; i++)
        printf("%d ", *(array++));
    printf("\n");
}

/* Draw the array */
void drawArray(int *array, int len) {
    char buffer[3];

    for(int i = 0; i < len; i++, array++) {
        DrawRectangleLines(20 + i * 50, 200, 40, 50, BLACK);
        intToString(*array, buffer);
        DrawText(buffer, 35 + i * 50, 215, 20, RAYWHITE);
    }
}

/* Convert an integer to string (used instead of snprint) */
void intToString(int num, char *str) {
    char *i = str;
    char *j;

    /* Take each digit and add it to the string (reversed) */
    if(num == 0)
        *str++ = '0';
    while(num > 0) {
        *str++ = (num % 10) + '0';
        num /= 10;
    }

    /* Reverse the string */
    for(j = str - 1; i < j; i++, j--) {
        char temp = *i;
        *i = *j;
        *j = temp;
    }

    *str = '\0';
}

/* Fill the array with random numbers from 0 to 99 */
void fillArray(int *array, int len) {
    for(int i = 0; i < len; i++, array++)
        *array = rand() % 100;
}