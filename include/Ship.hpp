#ifndef SHIP_HPP
#define SHIP_HPP

#include "MotionObject.hpp"

class Ship : public MotionObject {
    public:
        Ship();
        Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension);
        
        ~Ship();

        // Atualiza a nave em carga e posição
        void update(float delta_time);

        // Checa se a bala está carregada
        bool is_charged();

        // Dispara uma bala
        void fire_bullet();

        // Diminui a vida da nave
        int kill_ship();
    
    private:
        // Descrição da nave
        float _total_charge;
        float _current_charge; 

        int _life;
 
};



#endif