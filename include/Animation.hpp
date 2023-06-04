#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <raylib-cpp.hpp>
#include <string>
#include <map>

#include "MotionObject.hpp"

class MotionObject;

class Animation {
    public:
        Animation();
        Animation(Texture2D* texture, Vector2 tx_frames_dim, float frame_timer);

        ~Animation();

        void draw(MotionObject* motion_object);
        void update(float delta_timer);

    private:
        // Altera o frame a ser desenhado
        void _update_frame();

        // Adiciona tempo no relógio
        void _update_clock(float delta_time);

        // Textura
        Texture2D* _texture;

        // Dimensões da textura em pixels
        float _width;
        float _height;

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