#include <iostream>
#include <SDL2/SDL.h>
#define FPS_CAP  60
#define WINDOW_W 500
#define WINDOW_H 500

bool HasIntersection(SDL_FRect A, SDL_FRect B) {
    float L_A = A.x;
    float L_B = B.x;
    float R_A = A.x + A.w;
    float R_B = B.x + B.w;
    float T_A = A.y;
    float T_B = B.y;
    float B_A = A.y + A.h;
    float B_B = B.y + B.h;

    if (B_A <= T_B ||
        T_A >= B_B ||
        R_A <= L_B ||
        L_A >= R_B) {
        return false;
    }

    return true;
}

int main(void) {
    SDL_Init(SDL_INIT_EVERYTHING);
    const Uint8  *keyboard = SDL_GetKeyboardState(NULL);
    SDL_Event     event;
    SDL_Window   *window   = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    float DirX[] = {-3, -3, 3,  3};
    float DirY[] = {-3,  3, 3, -3};
    int direction = 0;

    /* playerOne stuff */
    SDL_FRect playerOne;
    playerOne.h = 60;
    playerOne.w = 10;
    playerOne.x = 40;
    playerOne.y = 250;

    SDL_FRect playerTwo;
    playerTwo.h = 60;
    playerTwo.w = 10;
    playerTwo.x = 450;
    playerTwo.y = 250;

    SDL_FRect ball;
    ball.h = 10;
    ball.w = 10;
    ball.x = (WINDOW_W / 2);
    ball.y = (WINDOW_H / 2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }

        if (keyboard[SDL_SCANCODE_UP]) {
            playerTwo.y -= 5;
        }

        if (keyboard[SDL_SCANCODE_DOWN]) {
            playerTwo.y += 5;
        }

        if (keyboard[SDL_SCANCODE_W]) {
            playerOne.y -= 5;
        }

        if (keyboard[SDL_SCANCODE_S]) {
            playerOne.y += 5;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRectF(renderer, &playerOne);
        SDL_RenderFillRectF(renderer, &playerTwo);
        SDL_RenderFillRectF(renderer, &ball);

        ball.x += DirX[direction];
        ball.y += DirY[direction];

        if (HasIntersection(playerOne, ball) == true ||
            HasIntersection(playerTwo, ball) == true) {
            direction += 1;
        }

        if (ball.x >= 500 || ball.x <= 0) { 
            ball.x = (WINDOW_W / 2);
            ball.y = (WINDOW_H / 2);
            direction += 2;
        }

        if (ball.y >= 490 || ball.y <= 0) {
            direction += 1;
        }

        if (direction >= 4) direction = 0;

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS_CAP);
    }
}