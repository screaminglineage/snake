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




void snake_update_body(Vector2 snake_pos[], size_t length) {
    for (size_t i = length - 1; i >= 1; i--) {
        snake_pos[i] = snake_pos[i-1];
    }
}


int main() {
    InitWindow(800, 600, "Snake");
    
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    SetTargetFPS(60);

    size_t length = 4;
    Vector2 snake_pos[] = {
        (Vector2){ width/2, height/2 },
        (Vector2){ width/2, height/2 + SNAKE_SIZE + SNAKE_PAD },
        (Vector2){ width/2, height/2 + 2*(SNAKE_SIZE + SNAKE_PAD) },
        (Vector2){ width/2, height/2 + 3*(SNAKE_SIZE + SNAKE_PAD) },
    };

    float elapsed = 0;
    Direction current_dir = Up;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        elapsed += dt;

        BeginDrawing();
        ClearBackground(BLACK);
        for (size_t i = 0; i < length; i++) {
            DrawText(TextFormat("%zu: %.2f %.2f", i, snake_pos[i].x, snake_pos[i].y), 0, i*(SNAKE_SIZE+SNAKE_PAD), 25, WHITE);
            Color color = (i == 0)? RED: GREEN;
            DrawRectangleV(snake_pos[i], (Vector2){SNAKE_SIZE, SNAKE_SIZE}, color);
        }

        if (snake_pos[0].x < 0) {
            snake_pos[0].x = width + snake_pos[0].x; 
        }
        if (snake_pos[0].x >= width) {
            snake_pos[0].x = snake_pos[0].x - width; 
        }
        if (snake_pos[0].y < 0) {
            snake_pos[0].y = height + snake_pos[0].y; 
        } 
        if (snake_pos[0].y >= height) {
            snake_pos[0].y = snake_pos[0].y - height; 
        }

        if (elapsed >= TICK_SPEED) { 
            elapsed = 0;
            snake_update_body(snake_pos, length);
            switch (current_dir) {
                case Up:
                    snake_pos[0].y -= (SNAKE_SIZE + SNAKE_PAD);
                    break;
                case Down:
                    snake_pos[0].y += (SNAKE_SIZE + SNAKE_PAD);
                    break;
                case Left:
                    snake_pos[0].x -= (SNAKE_SIZE + SNAKE_PAD);
                    break;
                case Right:
                    snake_pos[0].x += (SNAKE_SIZE + SNAKE_PAD);
                    break;
            }
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
