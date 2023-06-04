#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include <map>
#include <string>
#include <iterator>
#include <list>

#include "MotionObject.hpp"
#include "Behaviour.hpp"
#include "Settings.hpp"
#include "Animation.hpp"


class Animation;

class Game {
    public:
        Game();
        ~Game();

        // Configura janelas e inicializa objetos do jogo
        void initialize();

        // Render Loop
        void run_loop();

        // Fecha jogo
        void shutdown();
    
    private:
        // Recebe entradas do usuário (teclado e mouse)
        void _process_input();

        // Altera o estado do jogo com base nas entradas
        void _update_game();

        // Desenha o novo estado do jogo
        void _draw_game();

        // Carrega animações
        void inline _load_animations();

        // Carrega comportamentos
        void inline _load_behaviours();

        // Load graphics
        void inline _load_graphics();

        // Unload graphics
        void inline _unload_graphics();

        // Constrói objetos do joho
        void inline _build_objects();

        // Gráficos
        std::map<std::string, Texture2D> _textures;

        // Comportamento do jogo
        std::map<std::string, Behaviour*> _behaviours;

        // Animação do jogo
        Animation* _animation;

        // Objetos do jogo
        MotionObject* _motion_object;
        
};

#endif