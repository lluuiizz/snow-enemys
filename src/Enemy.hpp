#ifndef ENEMY_H_
#define ENEMY_H_

#include "RenderFunctions.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>


#define ACTIONS_COUNT 7
enum EnemyActions{
    MOVING,
    ATTACK, 
    IDLE
};

class Enemy {
        
    private:
        SDL_Rect crop_rect;
        SDL_Rect position_rect;
        SDL_Texture *sprites;

        float move_speed;
        float frame_counter;
        size_t frame_width, frame_height;
        size_t texture_width;

        EnemyActions curr_action;

        
        void update_frame(float delta);
    public:
        Enemy(SDL_Renderer *render_target, std::string sprites_path, size_t init_pos_x, size_t init_pos_y, size_t sprites_in_x_axys, size_t sprites_in_y_axys);
        ~Enemy();

        void Update(float delta, const Uint8 *key_state);
        void Draw(SDL_Renderer *render_target);

};
#endif


