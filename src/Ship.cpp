#include "Ship.hpp"
#include "Game.hpp"

Ship::Ship() : MotionObject() {

}

Ship::~Ship() {

}


Ship::Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension) 
    : MotionObject(position, velocity, acceleration, ship_dimension) {
        _total_charge = 0.5f; 
        _current_charge = 0.0f;
}

void Ship::update(float delta_time) {
    // Atualização relativa a comportamentos: posição, velocidade, aceleração
    MotionObject::update();

    // Atualização relativa a carga da bala
    if (is_charged() && _game->get_inputs("fire")) {
        // Crie uma bala e adicione ao estado do jogo
        fire_bullet();
        // Zerando a carga
        _current_charge = 0.0f;
        // Termine a função
        return;
    }

    // Carregue a bala
    _current_charge = is_charged() ? _total_charge : _current_charge + delta_time;

}

bool Ship::is_charged() {
    return _current_charge >= _total_charge;
}

void Ship::fire_bullet() {
    // Cria uma bala no topo da nave
    Vector2 bullet_position = Vector2Subtract(_parameters.at("position"), Vector2 {0, _parameters.at("dimension").y/2.0f});
    MotionObject* bullet = new MotionObject(bullet_position, Vector2 {0, -10}, Vector2 {0, 0}, Vector2 {30, 50});

    // Adiciona comportamento a bala
    bullet->add_behaviour(_game->get_behaviour("default-bullet"));

    // Adiciona animação a bala
    bullet->add_animation(_game->get_animation("bullet"));
    
    // Adicionae a bala so estado do jogo
    _game->add_bullet(bullet);
}