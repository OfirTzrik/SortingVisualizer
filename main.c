#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void) {
    /* Initialization */
    GuiLoadStyle("amber/style_amber.rgs");
    InitWindow(800, 600, "Sorting Visualizer");
    if(!IsWindowReady())
        return -1; /* Window failed to initialize */
    SetTargetFPS(60);

    float currentValue = 1;

    while(!WindowShouldClose()) {
        BeginDrawing();

        /* Content start */
        ClearBackground((Color){70, 70, 70, 255});
        DrawFPS(5, 5);
        
        GuiSlider((Rectangle){64, 32, 128, 16}, "Min: 1", "Max: 5", &currentValue, 1, 5);
        printf("%3.f\n", currentValue);

        /* Content end  */

        EndDrawing();
    }

    CloseWindow();
    return 0;
}