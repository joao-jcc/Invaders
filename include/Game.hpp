#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <list>

#include "Behaviour.hpp"
#include "Colors.hpp"
#include "Settings.hpp"
#include "Animation.hpp"
#include "MotionObject.hpp"
#include "Ship.hpp"

class Animation;
class Behaviour;


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

        // Adiciona bala
        void add_bullet(MotionObject* bullet);

        // Setter e Getters
        Behaviour* get_behaviour(std::string key);
        
        Animation* get_animation(std::string key);

        bool get_inputs(std::string key);

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

        // Constroi objetos do joho
        void inline _build_objects();

        // Gráficos
        std::map<std::string, Texture2D> _textures;

        // Comportamento do jogo
        std::map<std::string, Behaviour*> _behaviours;

        // Animação do jogo
        std::map<std::string, Animation*> _animations;

        // Objetos do jogo
        Ship* _ship;
        std::list<MotionObject*> _bullets;

        // Inputs
        std::map<std::string, bool> _key_inputs;
        Vector2 _mouse_position;
};

#endif