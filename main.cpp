#include "Perlin.hpp"
#include "Player.hpp"
#include <iostream>

#include <SDL.h>
#include <iomanip>
#include <chrono>


#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int xOrg = 100000;
int yOrg = 100000;
float freq = 0.4f;
int depth = 10;
double scale = 1;

double texture_x_shift = 0;
double texture_y_shift = 0;

double speed = (double)scale/1000;

void MovePixelsDownByOne(Uint32* pixels, SDL_PixelFormat* formatPix) {
    for (int y = 0; y < WIN_HEIGHT; y++) {
        for (int x = 0; x < WIN_WIDTH; x++) {
            if (y != WIN_HEIGHT - 1)
                pixels[y * WIN_WIDTH + x] = pixels[(y + 1) * WIN_WIDTH + x];
            else
            {
                float xCoord = xOrg + texture_x_shift + x / static_cast<float>(WIN_WIDTH) * scale;
                float yCoord = yOrg + texture_y_shift + y / static_cast<float>(WIN_HEIGHT) * scale;
                float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
                SDL_Color col = pickColor(static_cast<int>(value1 * 16) % 7);
                pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }
    }
}

void MovePixelsLeftByOne(Uint32* pixels, SDL_PixelFormat* formatPix) {
    for (int y = 0; y < WIN_HEIGHT; y++) {
        for (int x = WIN_WIDTH - 1; x >= 0; x--) {
            if (x != 0)
                pixels[y * WIN_WIDTH + x] = pixels[y * WIN_WIDTH + x - 1];
            else
            {
                float xCoord = xOrg + texture_x_shift + x / static_cast<float>(WIN_WIDTH) * scale;
                float yCoord = yOrg + texture_y_shift + y / static_cast<float>(WIN_HEIGHT) * scale;
                float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
                SDL_Color col = pickColor(static_cast<int>(value1 * 16) % 7);
                pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }
    }
}


void MovePixelsRightByOne(Uint32* pixels, SDL_PixelFormat* formatPix) {
    for (int y = 0; y < WIN_HEIGHT; y++) {
        for (int x = 0; x < WIN_WIDTH; x++) {
            if (x != WIN_WIDTH - 1)
                pixels[y * WIN_WIDTH + x] = pixels[y * WIN_WIDTH + x + 1];
            else
            {
                float xCoord = xOrg + texture_x_shift + x / static_cast<float>(WIN_WIDTH) * scale;
                float yCoord = yOrg + texture_y_shift + y / static_cast<float>(WIN_HEIGHT) * scale;
                float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
                SDL_Color col = pickColor(static_cast<int>(value1 * 16) % 7);
                pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }

    }
}

void MovePixelsUpByOne(Uint32* pixels, SDL_PixelFormat* formatPix) {
    for (int y = WIN_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIN_WIDTH; x++) {
            if (y != 0)
                pixels[y * WIN_WIDTH + x] = pixels[(y - 1) * WIN_WIDTH + x];
            else
            {
                float xCoord = xOrg + texture_x_shift + x / static_cast<float>(WIN_WIDTH) * scale;
                float yCoord = yOrg + texture_y_shift + y / static_cast<float>(WIN_HEIGHT) * scale;
                float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
                SDL_Color col = pickColor(static_cast<int>(value1 * 16) % 7);
                pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }
    }
}


void UpdatePixels(Uint32* pixels, SDL_PixelFormat* formatPix) {
    // Start timing with high resolution clock
    auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    for (int y = 0; y < WIN_HEIGHT; y++) {
        for (int x = 0; x < WIN_WIDTH; x++) {
            float xCoord = xOrg + texture_x_shift + x / static_cast<float>(WIN_WIDTH) * scale;
            float yCoord = yOrg + texture_y_shift + y / static_cast<float>(WIN_HEIGHT) * scale;
            float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
            SDL_Color col = pickColor(static_cast<int>(value1 * 16) % 7);
            pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
        }
    }

    // End timing with high resolution clock
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_taken = end - start;

    std::cout << "Time taken by func is : " << std::fixed
        << time_taken.count() << std::setprecision(5);
    std::cout << " sec " << std::endl;
}



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window* win = SDL_CreateWindow("perlin test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_PixelFormat* formatPix = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);

    Uint32* pixels = new Uint32[WIN_WIDTH * WIN_HEIGHT]; // Allocate pixels array on the heap
    UpdatePixels(pixels, formatPix);
    SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * WIN_WIDTH);

    Player p;
    bool quit = false;

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        bool updated = false;
        if (currentKeyStates[SDL_SCANCODE_W]) {
            texture_y_shift -= speed;
            MovePixelsUpByOne(pixels, formatPix);
            updated = true;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            texture_y_shift += speed;
            MovePixelsDownByOne(pixels, formatPix);
            updated = true;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            texture_x_shift -= speed;
            MovePixelsLeftByOne(pixels, formatPix);
            updated = true;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            texture_x_shift += speed;
            MovePixelsRightByOne(pixels, formatPix);
            updated = true;
        }

        if (updated) {
            //UpdatePixels(pixels, formatPix);
            //MovePixelsLeftByOne(pixels, formatPix);
            //std::cout << speed << "\n";
            SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * WIN_WIDTH);
        }

        SDL_RenderClear(renderer);
        SDL_Rect rect{ 0, 0, WIN_WIDTH, WIN_HEIGHT };
        SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        //SDL_Delay(15); // Cap frame rate
    }

    delete[] pixels; // Free the heap-allocated pixels array
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
