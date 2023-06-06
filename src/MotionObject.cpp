#include "MotionObject.hpp"

// Inicializando ponteiro para jogo como nulo
Game* MotionObject::_game = nullptr;

MotionObject::MotionObject() {

};

MotionObject::MotionObject(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 dimension) {
     _parameters = {{"position", position}, {"velocity", velocity}, 
                    {"acceleration", acceleration}, {"dimension", dimension}};

    // Comportamentos do objeto
    _behaviours = std::vector<Behaviour*>();

    // Animações do objeto
    _animations = std::vector<Animation*>();

    std::cout << TERMINAL_BOLDRED << "Game Pointer: " << _game << TERMINAL_RESET << std::endl;

};

MotionObject::~MotionObject() {

};

void MotionObject::update() {
    for (auto it = _behaviours.begin(); it != _behaviours.end(); it++) {
        (*it)->update(this);
    }

};

void MotionObject::draw() {
     for (auto it = _animations.begin(); it != _animations.end(); it++) {
        (*it)->draw(this);
    }
};

void MotionObject::add_behaviour(Behaviour* behaviour) {
    _behaviours.push_back(behaviour);
}

void MotionObject::add_animation(Animation* animation) {
    _animations.push_back(animation);
}

// Getters e Setters

void MotionObject::set(std::string key, Vector2 value) {
    _parameters.at(key) = value;
}

void MotionObject::set_game(Game* game) {
    _game = game;
}

Vector2 MotionObject::get(std::string key) {
    return _parameters.at(key);
}