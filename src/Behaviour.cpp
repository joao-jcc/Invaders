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


// KAMIKAZE_BEHAVIOUR

KamikazeBehaviour::KamikazeBehaviour(MotionObject* target_object) {
    // Ponteiro para o objeto perseguido
    _target_object = target_object;
    // Velocidade máxima que o alien kamikaze atinge
    _max_speed = 20.0f;
    // Taxa em que a aceleração é almentada JERK
    _acceleration_factor = 1.02f;
    // Velocidade em que os aliens perdem a manobrabilidade 
    _threshold_speed = _max_speed * (0.6f);

}

KamikazeBehaviour::~KamikazeBehaviour() {

}


void KamikazeBehaviour::update(MotionObject* motion_object) {
    
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");
    Vector2 acceleration = motion_object->get("acceleration");
    Vector2 direction = Vector2Subtract(_target_object->get("position"), position);
    
    acceleration = Vector2Scale(Vector2Normalize(direction), Vector2Length(acceleration));
    
    float velocity_length = Vector2Length(velocity);

   
    if (velocity_length < _threshold_speed) {
        velocity =  Vector2Scale(Vector2Normalize(direction), velocity_length);
    }

    velocity = Vector2Add(acceleration, velocity);
    velocity_length = Vector2Length(velocity);

    if (velocity_length > _max_speed) {
        velocity =  Vector2Scale(Vector2Normalize(velocity), _max_speed);
    }
    
    motion_object->set("velocity", velocity);
    motion_object->set("position", Vector2Add(velocity, position));
    motion_object->set("acceleration", Vector2Scale(acceleration, _acceleration_factor));

}