#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>
#include <string>

enum e_player_actions {
    UP, DOWN, LEFT, RIGHT,
    ATTACK, GRAB, IDLE
};

class Player {
    private:
        SDL_Rect crop_rect;
        SDL_Rect position_rect;
        SDL_Texture *sprites;

        float move_speed;
        float frame_counter;
        size_t sprite_frame_width, sprite_frame_height;
        size_t sprite_png_width;

        e_player_actions curr_action;
        SDL_Scancode player_key_actions[6];

    public:
        Player(SDL_Renderer *render_target, std::string sprites_path, size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys, size_t sprites_in_y_axys);
        ~Player();

        void Update(float delta, const Uint8 *key_state);
        void Draw(SDL_Renderer *render_target);


};

#endif
