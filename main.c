#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define SNAKE_SIZE 20
#define SNAKE_PAD 3
#define TICK_SPEED 0.5

typedef enum {
    Up,
    Down,
    Left,
    Right
} Direction;


typedef struct {
    int row;
    int col;
} Cell;


void snake_update_body(Cell snake_pos[], size_t length) {
    for (size_t i = length - 1; i >= 1; i--) {
        snake_pos[i] = snake_pos[i-1];
    }
}

int modulo(int a, int b) {
    return (a % b + b) % b;
}


int main() {
    InitWindow(800, 600, "Snake");
    
    int width = GetScreenWidth() / (SNAKE_SIZE + SNAKE_PAD);
    int height = GetScreenHeight() / (SNAKE_SIZE + SNAKE_PAD);
    SetTargetFPS(60);

    size_t length = 4;
    Cell snake_pos[] = {
        (Cell){ width/2, height/2 },
        (Cell){ width/2, height/2 + 1 },
        (Cell){ width/2, height/2 + 2 },
        (Cell){ width/2, height/2 + 3 }
    };

    float elapsed = 0;
    Direction current_dir = Up;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        elapsed += dt;

        BeginDrawing();
        ClearBackground(BLACK);
        for (size_t i = 0; i < length; i++) {
            DrawText(TextFormat("%zu: %d %d", i, snake_pos[i].col, snake_pos[i].row), 0, i*(SNAKE_SIZE+SNAKE_PAD), 25, WHITE);
            Color color = (i == 0)? RED: GREEN;
            Vector2 pos = (Vector2){ snake_pos[i].col * (SNAKE_SIZE + SNAKE_PAD), snake_pos[i].row * (SNAKE_SIZE + SNAKE_PAD) };
            DrawRectangleV(pos, (Vector2){SNAKE_SIZE, SNAKE_SIZE}, color);
        }
        
        if (elapsed >= TICK_SPEED) { 
            elapsed = 0;
            snake_update_body(snake_pos, length);
            switch (current_dir) {
                case Up:
                    snake_pos[0].row -= 1;
                    break;
                case Down:
                    snake_pos[0].row += 1;
                    break;
                case Left:
                    snake_pos[0].col -= 1;
                    break;
                case Right:
                    snake_pos[0].col += 1;
                    break;
            }
            snake_pos[0].row = modulo(snake_pos[0].row, height);
            snake_pos[0].col = modulo(snake_pos[0].col, width);
        }


        switch(GetKeyPressed()) {
            case KEY_UP: {
                if (current_dir != Up && current_dir != Down) {
                    current_dir = Up;
                    elapsed = TICK_SPEED;
                }
            }
            break;
            case KEY_DOWN: {
                if (current_dir != Up && current_dir != Down) {
                    current_dir = Down;
                    elapsed = TICK_SPEED;
                }
            }
            break;
            case KEY_LEFT: {
                if (current_dir != Left && current_dir != Right) {
                    current_dir = Left;
                    elapsed = TICK_SPEED;
                }
            }
            break;
            case KEY_RIGHT: {
                if (current_dir != Left && current_dir != Right) {
                    current_dir = Right;
                    elapsed = TICK_SPEED;
                }
            }
            break;
        }

        EndDrawing();
    }
}
