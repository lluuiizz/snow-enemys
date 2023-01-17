#include "GameObjs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>

IceFloor::IceFloor(SDL_Renderer *render_target, SDL_Window *window,std::string file_path) 
{
   SDL_Surface *surface = IMG_Load(file_path.c_str());
   static size_t row = 0;
   static size_t col = 0;

   if (surface == NULL) 
   {
        std::cout << "Error: " << IMG_GetError() << std::endl;
   }
   else
   {
        texture = SDL_CreateTextureFromSurface(render_target, surface);
   }

   if (texture == NULL) 
   {
        std::cout << "Error: " << SDL_GetError() << std::endl;
   }
   else 
   {
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

        position_rect.w = crop_rect.w *= 2;
        position_rect.h = crop_rect.h *= 2;


        int win_size_x, win_size_y;
        SDL_GetWindowSize(window, &win_size_x, &win_size_y);

        if (crop_rect.w * col >= win_size_x) 
        {
            row++;
            position_rect.x = col = 0;
            position_rect.y = crop_rect.h * row;

        }
        else
        {
            position_rect.x = crop_rect.w * col;
            position_rect.y = crop_rect.h * row;
            std::cout << col << " - pos_x: " << position_rect.x << " pos_y: " << position_rect.y << std::endl;
            col++;
        }

   }
}

IceFloor::~IceFloor() {
    SDL_DestroyTexture(texture);
    IMG_Quit();
}

void IceFloor::Draw(SDL_Renderer *render_target) {
    SDL_RenderCopy(render_target, texture, NULL, NULL);
}


