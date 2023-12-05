#ifndef RENDER_FUNCTIONS_H
#define RENDER_FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

SDL_Texture *get_texture(SDL_Renderer *render_target, std::string sprites_path);
void set_sprite_cfgs 
        (
        SDL_Texture *sprites, SDL_Rect *position_rect, SDL_Rect *crop_rect, size_t init_pos_x,
        size_t init_pos_y, size_t sprites_in_x_axys, size_t sprites_in_y_axys, size_t *texture_width,
        size_t *frame_height, size_t *frame_width
        );


#endif 
