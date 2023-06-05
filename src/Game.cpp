#include "Game.hpp"

Game::Game() {
   
   // Textures
   _textures = std::map<std::string, Texture2D>();
   // Comportamentos
   _behaviours = std::map<std::string, Behaviour*>();
}

Game::~Game() {
    // Deleta toda a memória alocada no HEAP
    delete _motion_object;

    for (std::pair<std::string, Behaviour*> behaviour_pair : _behaviours) {
        delete behaviour_pair.second;
    }

    delete _animation;
}

void Game::initialize() {
    // Inicializa a janela do jogo e estabelece o FPS
    SetTargetFPS(FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    // Carregando todas as texturas do jogo
    _load_graphics();

    // Criando as animações do jogo
    _load_animations();

    // Criando os comportamentos do jogo
    _load_behaviours();

    // Construindo os objetos: comportamento + animação
    _build_objects();
    
}

void Game::run_loop() {
    
    // Loop principal do jogo
 
     while(!WindowShouldClose()) {
        _process_input();
        _update_game();
        _draw_game();
    }

}

void Game::_process_input() {
    // Captura as entradas: mouse e teclado

}

void Game::_update_game() {
    // Altera o relógio das animações do jogo
    _animation->update(GetFrameTime());
    // Atualização da posição, velocidade e aceleração dos objetos cinemáticos
    _motion_object->update();
}

void Game::_draw_game() {
    // Desenha todos os objetos do jogo
    BeginDrawing();

    ClearBackground(BLACK);

    _motion_object->draw();

    EndDrawing();
}

void Game::shutdown() {
    _unload_graphics();
    CloseWindow();
}

void inline Game::_build_objects() {
    // Objetos do jogo
    Vector2 position = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}; // centro da tela
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 acceleration = {0.0f, 0.0f};
    Vector2 dimension = {50.0f, 80.0f};

    _motion_object = new MotionObject(position, velocity, acceleration, dimension);
    _motion_object->add_behaviour(_behaviours.at("follow-mouse"));
    _motion_object->add_animation(_animation);
}

void inline Game::_load_animations() {
    // Animação do jogo
    _animation = new AnimationFPS(&_textures.at("ship"), Vector2 {5, 2}, 0.1f);
    // _animation = new Animation(&_textures.at("bullet"));
}

void inline Game::_load_behaviours() {
    // Comportamentos do jogo
    _behaviours["follow-mouse"] = new FollowMouseBehaviour();
    _behaviours["default"] = new Behaviour();
}

void inline Game::_load_graphics() {
// Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = LoadTexture(BACKGROUND_TEXTURE);
    _textures["ship"] = LoadTexture(SHIP_TEXTURE);
    _textures["alien"] = LoadTexture(ALIEN_TEXTURE);
    _textures["bullet"] = LoadTexture(BULLET_TEXTURE);
    _textures["explosion"] = LoadTexture(EXPLOSION_TEXTURE);
    _textures["power-up"] = LoadTexture(POWERUP_TEXTURE);                       

}

void inline Game::_unload_graphics() {
     // Libera memória alocada para os gráficos/texturas
    for (std::pair<std::string, Texture2D> tx_pair : _textures) {
        UnloadTexture(tx_pair.second);
    }
}
