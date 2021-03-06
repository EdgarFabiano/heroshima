//
// Created by edgar on 29/05/18.
//

#include "Gravity.h"

Gravity::Gravity(GameObject &associated) : Component(associated) {

    this->verticalSpeed = 0;
    this->speed = {0,0};
}

void Gravity::Update(float dt) {
    verticalSpeed += GRAVITY * dt;
    if (verticalSpeed > GRAVITY_LIMIT) {
        verticalSpeed = GRAVITY_LIMIT;
    }
    speed = Vec2(0, verticalSpeed);
    associated.box += speed;
}

void Gravity::Render() {}

bool Gravity::Is(string type) {
    return type == GRAVITY_TYPE;
}

float Gravity::GetVerticalSpeed() const {
    return verticalSpeed;
}

void Gravity::SetVerticalSpeed(float verticalSpeed) {
    this->verticalSpeed = verticalSpeed;
}

float Gravity::GetGravityAcc() {
    return GRAVITY;
}
