#include "Game.hpp"

Game::Game() {
    // Inputs
    _key_inputs = { {"move-right", false}, {"move-left", false}, {"fire", false}};
    _mouse_position = Vector2 {};
   
    // Textures
    _textures = std::map<std::string, Texture2D>();
    // Animações
    _animations = std::map<std::string, Animation*>();
    // Comportamentos
    _behaviours = std::map<std::string, Behaviour*>();
    // Objetos
    _ship = nullptr;
    _bullets = std::list<MotionObject*>();

    // Ponteiro para o jogo para as instâncias MotionObject;
    MotionObject motion_object;
    motion_object.set_game(this);

}

Game::~Game() {
    // Deleta toda a memória alocada no HEAP
    delete _ship;

    for (std::pair<std::string, Behaviour*> behaviour_pair : _behaviours) {
        delete behaviour_pair.second;
    }

    for (std::pair<std::string, Animation*> animation_pair : _animations) {
        delete animation_pair.second;
    }

    for (MotionObject* bullet : _bullets) {
        delete bullet;
    }

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
    _mouse_position = GetMousePosition();

    _key_inputs.at("move-right") = IsKeyDown(MOVE_RIGHT_KEY);
    _key_inputs.at("move-left") = IsKeyDown(MOVE_LEFT_KEY);
    _key_inputs.at("fire") = IsKeyDown(FIRE_KEY);

}

void Game::_update_game() {
    // Altera o relógio das animações do jogo
    float time = GetFrameTime();
    for (std::pair<std::string, Animation*> animation_pair : _animations) {
        animation_pair.second->update(time);
    }
    
    // Atualiza a posição das balas
    for (MotionObject* bullet : _bullets) {
        bullet->update(); 
    }
    // Atualização a nave do jogador
    _ship->update(time);
}

void Game::_draw_game() {
    // Desenha todos os objetos do jogo
    BeginDrawing();

    ClearBackground(BLACK);

     // Desenha o background com a textura especificada
    Texture2D bg_texture = _textures.at("background");
    DrawTexturePro(bg_texture, (Rectangle) {0, 0, (float) bg_texture.width, (float) bg_texture.height}, 
    (Rectangle) {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, 
    Vector2Zero(), 0, WHITE);

    for (MotionObject* bullet : _bullets) {
        bullet->draw();
    }

    _ship->draw();

    EndDrawing();
}

void Game::shutdown() {
    _unload_graphics();
    CloseWindow();
}

void inline Game::_build_objects() {
    // Objetos do jogo
    Vector2 velocity = {10.0f, 0.0f};
    Vector2 acceleration = {0.0f, 0.0f};
    Vector2 dimension = {200.0f, 200.0f};
    // Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT - dimension.y/2.0f};
    Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2.0f};

    _ship = new Ship(position, velocity, acceleration, dimension);
    _ship->add_behaviour(_behaviours.at("default-ship"));
    _ship->add_animation(_animations.at("ship"));
}

void inline Game::_load_animations() {
    // Animação do jogo
    // _animations["explosion"] = new AnimationFPS(&_textures.at("explosion"), Vector2 {5, 1}, 0.1f);
    _animations["alien"] = new AnimationFPS(&_textures.at("alien"), Vector2 {4, 4}, 0.2f);
    _animations["ship"] = new AnimationFPS(& _textures.at("ship"), Vector2 {4, 3}, 0.2f);
    _animations["bullet"] = new AnimationFPS(&_textures.at("bullet"), Vector2 {4, 3}, 0.2f);
}

void inline Game::_load_behaviours() {
    // Comportamentos do jogo
    _behaviours["follow-mouse"] = new FollowMouseBehaviour();
    _behaviours["default"] = new Behaviour();
    _behaviours["default-ship"] = new DefaultShipBehaviour(&_key_inputs);
    _behaviours["default-bullet"] = new DefaultBulletBehaviour();
}

void inline Game::_load_graphics() {
    // Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = LoadTexture(BACKGROUND_TEXTURE);
    // _textures["explosion"] = LoadTexture(EXPLOSION_TEXTURE);
    // _textures["power-up"] = LoadTexture(POWERUP_TEXTURE);    

    _textures["ship"] = LoadTexture(SHIP_TEXTURE);
    _textures["alien"] = LoadTexture(ALIEN_TEXTURE);
    _textures["bullet"] = LoadTexture(BULLET_TEXTURE);                   

}

void inline Game::_unload_graphics() {
     // Libera memória alocada para os gráficos/texturas
    for (std::pair<std::string, Texture2D> tx_pair : _textures) {
        UnloadTexture(tx_pair.second);
    }
}

void Game::add_bullet(MotionObject* bullet) {
    _bullets.push_back(bullet);
}

Behaviour* Game::get_behaviour(std::string key) {
    return _behaviours.at(key);
}

Animation* Game::get_animation(std::string key) {
    return _animations.at(key);
}

 bool Game::get_inputs(std::string key){
    return _key_inputs.at(key);
 }