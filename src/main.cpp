#include <raylib-cpp.hpp>

#include "Game.hpp"

int main() {
    
    // Initialization
    Game invaders;

    invaders.initialize();
    invaders.run_loop();
    invaders.shutdown();
    
    return 0;
}