#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <raylib-cpp.hpp>
#include <map>
#include <iostream>

#include "MotionObject.hpp"
#include "Colors.hpp"
#include "Settings.hpp"

class MotionObject;

// Determina o comportamento cinemático do objeto (posicao e velocidade)
class Behaviour {
    public:
        Behaviour();
        ~Behaviour();

        virtual void update(MotionObject* motion_object);

};


class FollowMouseBehaviour : public Behaviour {
    public:
        FollowMouseBehaviour();
        ~FollowMouseBehaviour();

        void update(MotionObject* motion_object) override;
};

#endif