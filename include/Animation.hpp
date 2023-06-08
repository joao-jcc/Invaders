#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Game.hpp"
#include "MotionObject.hpp"

class Game;
class MotionObject;

class Animation {
    public:
        Animation();
        Animation(Texture2D* texture);
        ~Animation();

        void virtual draw(MotionObject* motion_object);
        void virtual update(float delta_time);
    
    protected:
        // Textura
        Texture2D* _texture;

        // Dimensões da textura em pixels
        float _width;
        float _height;
};

class AnimationFPS : public Animation {
    public:
        AnimationFPS();
        AnimationFPS(Texture2D* texture, Vector2 tx_frames_dim, float frame_timer);

        ~AnimationFPS();

        void draw(MotionObject* motion_object) override;
        void update(float delta_time) override;

    private:
        // Altera o frame a ser desenhado
        void _update_frame();

        // Adiciona tempo no relógio
        void _update_clock(float delta_time);

        // Número total de frames na textura
        float _num_frames;

        // Disposição dos frames na textura
        Vector2 _tx_frame_dim;

        // Frame corrente
        float _frame;

        // Tempo para mundança do frame
        float _frame_timer;

        // Armazena o tempo corrente em segundos
        float _clock;

        
};

#endif