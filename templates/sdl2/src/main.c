#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);

  if (window == NULL) {
    fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  char *image_path = "assets/smiley.bmp";
  SDL_Surface *bmp = SDL_LoadBMP(image_path);
  if (bmp == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fprintf(stderr, "Failed to load image: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, bmp);
  SDL_FreeSurface(bmp);
  if (tex == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fprintf(stderr, "Failed to free surface: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  SDL_Event e;
  int  quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_q ||
              e.key.keysym.sym == SDLK_ESCAPE)
              quit = 1;
          break;
      }
    }

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, tex, NULL, NULL);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
