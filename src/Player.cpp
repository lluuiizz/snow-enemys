#include "Player.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

Player::Player(
        SDL_Renderer *render_target, std::string sprites_path,
        size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys,
        size_t sprites_in_y_axys
        )
{
    SDL_Surface *surface = IMG_Load(sprites_path.c_str());

    bool error_ocurred = false;

    if (surface == NULL)
    {
        std::cout << "Error at creating surface: " << SDL_GetError() << std::endl;
        error_ocurred = true;
    }
    else
    {
        sprites = SDL_CreateTextureFromSurface(render_target, surface);
        if (sprites == NULL) 
        {
            std::cout << "Error at creating texture: " << SDL_GetError() << std::endl;
            error_ocurred = true;
        }
    }

    if (!error_ocurred) 
    {
        SDL_FreeSurface(surface); 
        SDL_QueryTexture(sprites, NULL, NULL, &crop_rect.w, &crop_rect.h);

        position_rect.x = init_pos_x;
        position_rect.y = init_pos_y;

        sprite_png_width = crop_rect.w;
        
        crop_rect.w /= sprites_in_x_axys;
        crop_rect.h /= sprites_in_y_axys;


        sprite_frame_width = position_rect.w = crop_rect.w;
        sprite_frame_height = position_rect.h = crop_rect.h;

        position_rect.w *= 2;
        position_rect.h *= 2;

        crop_rect.x = crop_rect.y = 0;

        curr_action = IDLE;

        player_key_actions[UP] = SDL_SCANCODE_W;
        player_key_actions[LEFT] = SDL_SCANCODE_A;
        player_key_actions[DOWN] = SDL_SCANCODE_S;
        player_key_actions[RIGHT] = SDL_SCANCODE_D;
        player_key_actions[ATTACK] = SDL_SCANCODE_SPACE;
        player_key_actions[GRAB] = SDL_SCANCODE_Q;

        move_speed = 250.0f;

    }

}

Player::~Player() 
{
    SDL_DestroyTexture(sprites);
}

void Player::Update(float delta, const Uint8 *key_state) {

    if (key_state[player_key_actions[UP]])
    {
        position_rect.y -= move_speed * delta;
        curr_action = UP;

    }
    else if (key_state[player_key_actions[RIGHT]]) 
    {
        position_rect.x += move_speed * delta;
        curr_action = RIGHT;

    }
    else if (key_state[player_key_actions[LEFT]]) 
    {
        position_rect.x -= move_speed * delta;
        curr_action = LEFT;

    }

    else if (key_state[player_key_actions[DOWN]]) 
    {
        position_rect.y += move_speed * delta;
        curr_action = DOWN;
    }

    else 
    {
        curr_action = IDLE;
    }

    frame_counter += delta;

    if(frame_counter >= 0.5f) 
    {
        frame_counter = 0;

        switch (curr_action) 
        {
            case UP:
                break;
            case DOWN:
                crop_rect.y = 0;
                crop_rect.x += sprite_frame_width;
                break;
            case RIGHT:
                crop_rect.y = sprite_frame_height;
                crop_rect.x += sprite_frame_width;
                break;
            case LEFT:
                crop_rect.y = sprite_frame_height;
                crop_rect.x += sprite_frame_width;
                break;
            case IDLE:
                crop_rect.y = 0;
                crop_rect.x += sprite_frame_width;
                break;
            default:
                break;
        }
        if (crop_rect.x >= sprite_png_width)
        {
            crop_rect.x = 0;
        }
    }


}

void Player::Draw(SDL_Renderer *render_target) 
{
    if (curr_action == LEFT)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(render_target, sprites, &crop_rect, &position_rect, 0, NULL, flip);

    }
    else 
        SDL_RenderCopy(render_target, sprites, &crop_rect, &position_rect);
}
