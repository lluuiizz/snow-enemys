#ifndef GAME_OBJS_H
#define GAME_OBJS_H

#include <SDL2/SDL.h>
#include <string>

class IceFloor {
    private:
        SDL_Texture *texture;
        SDL_Rect crop_rect;
        SDL_Rect position_rect;
         
    public:
        IceFloor();
        IceFloor(SDL_Renderer *render_target, SDL_Window *window, std::string file_path);
        ~IceFloor();

        void Draw(SDL_Renderer *render_target);
};


#endif 
