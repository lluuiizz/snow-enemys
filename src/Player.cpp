#include "Player.hpp"
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

    position_rect->w *= 2;
    position_rect->h *= 2;

    crop_rect->x = crop_rect->y = 0;

}

void set_player_keys(std::vector<SDL_Scancode> player_action_keys) 
{
    player_action_keys[UP] = SDL_SCANCODE_W;
    player_action_keys[LEFT] = SDL_SCANCODE_A;
    player_action_keys[DOWN] = SDL_SCANCODE_S;
    player_action_keys[RIGHT] = SDL_SCANCODE_D;
    player_action_keys[ATTACK] = SDL_SCANCODE_SPACE;
    player_action_keys[GRAB] = SDL_SCANCODE_Q;
}

SDL_Texture *get_texture(SDL_Renderer *render_target, std::string sprites_path) 
{
    SDL_Surface *surface = IMG_Load(sprites_path.c_str());
    SDL_Texture *texture = nullptr;

    if (surface == NULL)
    {
        std::cout << "Error at creating surface: " << SDL_GetError() << std::endl;
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
void Player::key_handler(float delta, const Uint8 *key_state) 
{

    if (key_state[player_action_keys[UP]])
    {
        position_rect.y -= move_speed * delta;
        curr_action = UP;

    }
    else if (key_state[player_action_keys[RIGHT]]) 
    {
        position_rect.x += move_speed * delta;
        curr_action = RIGHT;

    }
    else if (key_state[player_action_keys[LEFT]]) 
    {
        position_rect.x -= move_speed * delta;
        curr_action = LEFT;

    }

    else if (key_state[player_action_keys[DOWN]]) 
    {
        position_rect.y += move_speed * delta;
        curr_action = DOWN;
    }

    else 
    {
        curr_action = IDLE;
    }


}

void Player::update_frame(float delta) 
{

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
                crop_rect.x += frame_width;
                break;
            case RIGHT:
                crop_rect.y = frame_height;
                crop_rect.x += frame_width;
                break;
            case LEFT:
                crop_rect.y = frame_height;
                crop_rect.x += frame_width;
                break;
            case IDLE:
                crop_rect.y = 0;
                crop_rect.x += frame_width;
                break;
            default:
                break;
        }
        if (crop_rect.x >= texture_width)
        {
            crop_rect.x = 0;
        }
    }
}
//////////////////////////////////////////////
Player::Player(
        SDL_Renderer *render_target, std::string sprites_path,
        size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys,
        size_t sprites_in_y_axys
        )
{

    sprites = get_texture(render_target, sprites_path);
    set_sprite_cfgs(sprites, &position_rect, &crop_rect, init_pos_x, init_pos_y, sprites_in_x_axys, sprites_in_y_axys, &texture_width, &frame_height, &frame_width);
    set_player_keys(player_action_keys);

    curr_action = IDLE;
    move_speed = 250.0f;

}

void Player::Update(float delta, const Uint8 *key_state) 
{

    key_handler(delta, key_state);
    update_frame(delta);
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

Player::~Player() 
{
    SDL_DestroyTexture(sprites);
}


