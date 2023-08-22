#include <iostream>
#include <vector>
#include <SDL.h>

const int screenWidth = 800;
const int screenHeight = 600;
const int ballRadius = 20;
const int ballVelocity = 5;

struct Ball {
    int x, y;
    int dx, dy;
};

std::vector<Ball> balls;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_CreateWindow("Bouncing Balls Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    return true;
}

void createBalls(int numBalls) {
    for (int i = 0; i < numBalls; ++i) {
        Ball ball;
        ball.x = rand() % (screenWidth - ballRadius * 2) + ballRadius;
        ball.y = rand() % (screenHeight - ballRadius * 2) + ballRadius;
        ball.dx = rand() % (2 * ballVelocity) - ballVelocity;
        ball.dy = rand() % (2 * ballVelocity) - ballVelocity;
        balls.push_back(ball);
    }
}

void updateBalls() {
    for (auto& ball : balls) {
        ball.x += ball.dx;
        ball.y += ball.dy;

        if (ball.x - ballRadius < 0 || ball.x + ballRadius > screenWidth) {
            ball.dx = -ball.dx;
        }

        if (ball.y - ballRadius < 0 || ball.y + ballRadius > screenHeight) {
            ball.dy = -ball.dy;
        }
    }
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (const auto& ball : balls) {
        SDL_Rect rect = {ball.x - ballRadius, ball.y - ballRadius, ballRadius * 2, ballRadius * 2};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

int main() {
    if (!initializeSDL()) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Bouncing Balls Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    createBalls(10);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        updateBalls();
        render(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
