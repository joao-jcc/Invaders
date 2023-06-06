#ifndef MOTION_OBJECT_H
#define MOTION_OBJECT_H

#include <raylib-cpp.hpp>
#include <vector>
#include <iterator>
#include <map>
#include <string>

#include "Game.hpp"
#include "Behaviour.hpp"
#include "Animation.hpp"

class Game;
class Behaviour;
class Animation;

class MotionObject {
    public:
        // Construtor padrão
        MotionObject();

        // Construtor com especificação dos estado
        MotionObject(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 dimension);

        // Destrutor
        ~MotionObject();

        // Atualiza a posição do objeto com base em comportamentos
        void update();

        // Desenha o objeto com base nas animações em seu estado
        void draw();

        // Adiciona comportamentos para modificar a função update
        void add_behaviour(Behaviour* behaviour);

        // Adiciona animação para modificar a função draw
        void add_animation(Animation* animation);

        // Getters e Setters para parâmtros de movimento e dimensão
        void set(std::string key, Vector2 value);
        Vector2 get(std::string key);

        // Setter para o ponteiro do jogo
        void set_game(Game* game);

    protected:
        static Game* _game;
        // Posição, Velocidade, Aceleração e Dimensão
        std::map<std::string, Vector2> _parameters;

        // Comportamentos do objeto
        std::vector<Behaviour*> _behaviours;

        // Animações do objeto
        std::vector<Animation*> _animations;

};

#endif