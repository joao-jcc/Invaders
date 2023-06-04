#include "Behaviour.hpp"

// BEHAVIOUR
Behaviour::Behaviour() {
    
};

Behaviour::~Behaviour() {

};

void Behaviour::update(MotionObject* motion_object) {
    // Posição no centro da tela
    Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

    motion_object->set("position", position);

}

// FOLLOW_MOUSE_BEHAVIOUR
FollowMouseBehaviour::FollowMouseBehaviour() {

};

FollowMouseBehaviour::~FollowMouseBehaviour() {

};

void FollowMouseBehaviour::update(MotionObject* motion_object) {
    motion_object->set("position", GetMousePosition());
};


