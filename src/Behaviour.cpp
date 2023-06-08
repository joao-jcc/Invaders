#include "Behaviour.hpp"

// BEHAVIOUR
Behaviour::Behaviour() {
    
};

Behaviour::~Behaviour() {

};

void Behaviour::update(MotionObject* motion_object) {
    // Posição no centro da tela
    Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

    // Posiciona o objeto no centro da tela
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


// DEFAULT_SHIP_BEHAVIOUR

DefaultShipBehaviour::DefaultShipBehaviour(std::map<std::string, bool>* key_inputs)
    : _key_inputs(key_inputs) {
}


DefaultShipBehaviour::~DefaultShipBehaviour() {

}

void DefaultShipBehaviour::update(MotionObject* motion_object) {
    // Movimento retilíneo e uniforme da nave (velocidade constante e aceleração nula)
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");
    float width = motion_object->get("dimension").x;

    // std::cout << TERMINAL_BOLDCYAN << width/2.0f << TERMINAL_RESET << std::endl;

    bool move_right = _key_inputs->at("move-right"), move_left = _key_inputs->at("move-left");
    position.x += move_right * velocity.x - move_left * velocity.x;
    
    // Checa fronteiras laterais: substituir o 20 por um valor em função da dimensão da nave
    if (position.x > width/2.2f && position.x < SCREEN_WIDTH - width/2.2f)
        motion_object->set("position", position);

    motion_object->set("velocity", velocity);
}

// DEFAULT_BULLET_BEHAVIOUR
DefaultBulletBehaviour::DefaultBulletBehaviour() {

}

DefaultBulletBehaviour::~DefaultBulletBehaviour() {

}

void DefaultBulletBehaviour::update(MotionObject* motion_object) {
     // Movimento retilíneo e uniforme vertical da bala
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");

    motion_object->set("position", Vector2Add(position, velocity));
}