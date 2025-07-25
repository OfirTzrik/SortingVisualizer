#include <raylib.h>
#include "raygui.h"

int main(void) {
    InitWindow(800, 600, "Sorting Visualizer");
    if(!IsWindowReady())
        return -1; /* Window failed to initialize */
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        /* Content start */
        ClearBackground(RAYWHITE);
        DrawFPS(5, 5);

        /* Content end  */

        EndDrawing();
    }

    CloseWindow();
    return 0;
}