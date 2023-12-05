#include "Enemy.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

//  Functions to Constructor
void set_sprite_cfgs 
        (
        SDL_Texture *sprites, SDL_Rect *position_rect, SDL_Rect *crop_rect, size_t init_pos_x,
        size_t init_pos_y, size_t sprites_in_x_axys, size_t sprites_in_y_axys, size_t *texture_width,
        size_t *frame_height, size_t *frame_width
        )
{
    SDL_QueryTexture(sprites, NULL, NULL, &crop_rect->w, &crop_rect->h);

    position_rect->x = init_pos_x;
    position_rect->y = init_pos_y;

    *texture_width = crop_rect->w;
    
    crop_rect->w /= sprites_in_x_axys;
    crop_rect->h /= sprites_in_y_axys;


    *frame_width = position_rect->w = crop_rect->w;
    *frame_height = position_rect->h = crop_rect->h;

    position_rect->w *= 4;
    position_rect->h *= 4;

    crop_rect->x = crop_rect->y = 0;

}


SDL_Texture *get_texture(SDL_Renderer *render_target, std::string sprites_path) 
{
    SDL_Surface *surface = IMG_Load(sprites_path.c_str());
    SDL_Texture *texture = nullptr;

    if (surface == NULL)
    {
        std::cout << "Error at creating surface: " << IMG_GetError() << std::endl;
        return NULL;
    }
    else 
        texture = SDL_CreateTextureFromSurface(render_target, surface);
    

    if (texture == NULL) 
    {
        std::cout << "Error at creating texture: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_FreeSurface(surface);

    return texture;

}

//  Private methods of Update public method

void Enemy::update_frame(float delta) 
{
    //  To Do
}
//////////////////////////////////////////////
Enemy::Enemy(
        SDL_Renderer *render_target, std::string sprites_path,
        size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys,
        size_t sprites_in_y_axys
        )
{

    sprites = get_texture(render_target, sprites_path);
    set_sprite_cfgs(sprites, &position_rect, &crop_rect, init_pos_x, init_pos_y, sprites_in_x_axys, sprites_in_y_axys, &texture_width, &frame_height, &frame_width);

    curr_action = IDLE;
    move_speed = 300.0f;

}

void Enemy::Update(float delta, const Uint8 *key_state) 
{
    update_frame(delta);
}

void Enemy::Draw(SDL_Renderer *render_target) 
{
    SDL_RenderCopy(render_target, sprites, &crop_rect, &position_rect);
}

Enemy::~Enemy() 
{
    SDL_DestroyTexture(sprites);
    IMG_Quit();
    sprites = nullptr;
}

