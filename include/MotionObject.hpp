#ifndef MOTION_OBJECT_HPP
#define MOTION_OBJECT_HPP


#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>


class Game;
class Behaviour;
class Animation;

class MotionObject {
    public:
        // Construtor padrão
        MotionObject();

        // Construtor com especificação do estado
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

        // Getters e Setters para parâmetros de movimento e dimensão
        void set(std::string key, Vector2 value);
        Vector2 get(std::string key);

        // Getter para o retângulo do MotionObject
        Rectangle get_rectangle();

        // Setter para o ponteiro do jogo
        void set_game(Game* game);

    protected:
        // Ponteiro para o jogo
        static Game* _game;

        // Posição, Velocidade, Aceleração e Dimensão
        std::map<std::string, Vector2> _parameters;

        // Representação retangular do objeto
        Rectangle _rectangle;

        // Comportamentos do objeto
        std::vector<Behaviour*> _behaviours;

        // Animações do objeto
        std::vector<Animation*> _animations;

        // Modifica a posição do retângulo
        void _update_rectangle();
};

#endif