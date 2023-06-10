#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "MotionObject.hpp"

class Alien : public MotionObject {
    public:
        Alien();
        Alien(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 alien_dimension);
        
        ~Alien();

        // Getter
        unsigned get_score();
    
    protected:
        // Score do alien
        unsigned _score;
};



#endif