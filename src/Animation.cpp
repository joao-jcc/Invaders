#include "Animation.hpp"

Animation::Animation() {

}

Animation::Animation(Texture2D* texture) {
    _texture = texture;
    _width = texture->width;
    _height = texture->height;
}

Animation::~Animation() {

}


void Animation::draw(MotionObject* motion_object) {
    Vector2 position = motion_object->get("position");
    Vector2 dimension = motion_object->get("dimension");
    
    DrawTexturePro(*_texture, (Rectangle) {0, 0, _width, _height},
    (Rectangle) {position.x, position.y, dimension.x, dimension.y},
    Vector2 {dimension.x/2, dimension.y/2}, 0, WHITE);
}

void Animation::update(float delta_time) {

}

AnimationFPS::AnimationFPS() : Animation() {

}

AnimationFPS::AnimationFPS(Texture2D* texture, Vector2 tx_frame_dim, float frame_timer) : Animation(texture) {
    _num_frames = tx_frame_dim.x * tx_frame_dim.y;
    _tx_frame_dim = tx_frame_dim;
    _clock = 0.0f;
    _frame_timer = frame_timer;
    _frame = 0;
}

AnimationFPS::~AnimationFPS() {

}

void AnimationFPS::update(float delta_time) {
    _clock += delta_time;
    _update_frame();
}

void AnimationFPS::_update_frame() {
    if (_clock >= _frame_timer) {
        _frame = _frame == _num_frames - 1 ? 0 : _frame+1;
        _clock = 0.0f;
    }
}

void AnimationFPS::draw(MotionObject* motion_object) {
    Vector2 position = motion_object->get("position");
    Vector2 dimension = motion_object->get("dimension");

    float idy = (float) ((unsigned)_frame / (unsigned)_tx_frame_dim.x);
    float idx = (float) ((unsigned)_frame % (unsigned)_tx_frame_dim.x);
    
    DrawTexturePro(*_texture, 
    (Rectangle) {idx * (_width/_tx_frame_dim.x), idy * (_height/_tx_frame_dim.y), _width/_tx_frame_dim.x, _height/_tx_frame_dim.y},
    (Rectangle) {position.x, position.y, dimension.x, dimension.y},
    Vector2 {dimension.x/2, dimension.y/2}, 0, WHITE);
};