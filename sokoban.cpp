#include <raylib.h>

int main(void)
{
    InitWindow(800, 450, "Wil gostosão - janela básica");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Parabéns, Wil! Você é um gostosão", 190, 200, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}