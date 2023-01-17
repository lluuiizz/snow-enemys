#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#define ACTIONS_COUNT 7
enum PlayerActions {
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
        size_t frame_width, frame_height;
        size_t texture_width;

        PlayerActions curr_action;
        SDL_Scancode player_action_keys[ACTIONS_COUNT];

        void key_handler(float delta, const Uint8 *key_state);
        void update_frame(float delta);

    public:
        Player(SDL_Renderer *render_target, std::string sprites_path, size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys, size_t sprites_in_y_axys);
        ~Player();

        void Update(float delta, const Uint8 *key_state);
        void Draw(SDL_Renderer *render_target);


};

#endif
