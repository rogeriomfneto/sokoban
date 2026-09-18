#include <raylib.h>



void update();
void draw();


int main(void) {
    InitWindow(800, 450, "Wil gostosão - janela básica");

    while (!WindowShouldClose())
    {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}

void update() {

}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Parabéns, Wil! Você é um gostosão", 190, 200, 20, WHITE);
    EndDrawing();
}