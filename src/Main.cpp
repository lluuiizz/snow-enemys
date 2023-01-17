#include <iostream>
#include <SDL2/SDL.h>
#include "Player.hpp"

#define WIDTH 1280
#define HEIGHT 720

int main(void) {

   SDL_Window *window = nullptr; 
   SDL_Renderer *render = nullptr;

   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
       std::cout << "Init Video Error: " << SDL_GetError() << std::endl;
   }

   window = SDL_CreateWindow("Snow Enemys", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );

   if (window == NULL) {
       std::cout << "Init Window Error: " << SDL_GetError() << std::endl;
   }

   render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   //   Frame managnment
   int prev_time = 0;
   int curr_time = 0;
   float delta_time = 0.0f;

   //   Keyboard state
   const Uint8 *key_state;

   //   Game Window Status
   bool is_running = true;

   //   Event Holder? Don't know a good name
   SDL_Event ev;

   //   Instantiates Player
   Player player(render, "../sprites/Player/player.png", 0, 0, 2, 3);

   SDL_SetRenderDrawColor(render, 0xFF,0xFF,0xFF,0xFF);

   while (is_running) {
       //   Frames
       prev_time = curr_time;
       curr_time = SDL_GetTicks();
       delta_time = (curr_time - prev_time) / 1000.0f;

       //   Events
       while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                is_running = false;
            }
       }

       key_state = SDL_GetKeyboardState(NULL); //   Get all key inputs
                                               
                                    
       SDL_RenderClear(render);
       player.Update(delta_time, key_state);
       player.Draw(render);
       SDL_RenderPresent(render);
   }


   window = nullptr;
   render = nullptr;

   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(render);
   SDL_Quit();

   return 0;

}
