//
// Created by edgar on 26/04/18.
//

#include <Game.h>
#include "Camera.h"
#include "InputManager.h"
#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {

    Rect aux = Rect();

    aux.w = associated.box.w * scale.x;
    aux.h = associated.box.h * scale.y;

    const Vec2 &center = associated.box.GetCenter();
    aux.x = center.x - aux.w / 2;
    aux.y = center.y - aux.h / 2;

    this->box = aux + offset.RotateDeg((float)(associated.angleDeg));
}

void Collider::Update(float dt) {

    Rect aux = Rect();

    aux.w = associated.box.w * scale.x;
    aux.h = associated.box.h * scale.y;

    const Vec2 &center = associated.box.GetCenter();
    aux.x = center.x - aux.w / 2;
    aux.y = center.y - aux.h / 2;

    this->box = aux + offset.RotateDeg((float)(associated.angleDeg));
}

void Collider::Render() {
    if(Game::GetInstance().GetCurrentState().isDebug()) {
        Vec2 center(box.GetCenter());
        SDL_Point points[5];

        Vec2 point = (Vec2(box.x, box.y) - center).RotateDeg((float) (associated.angleDeg))
                     + center - Camera::pos;
        points[0] = {(int) point.x, (int) point.y};
        points[4] = {(int) point.x, (int) point.y};

        point = (Vec2(box.x + box.w, box.y) - center).RotateDeg((float) (associated.angleDeg))
                + center - Camera::pos;
        points[1] = {(int) point.x, (int) point.y};

        point = (Vec2(box.x + box.w, box.y + box.h) - center).RotateDeg((float) (associated.angleDeg))
                + center - Camera::pos;
        points[2] = {(int) point.x, (int) point.y};

        point = (Vec2(box.x, box.y + box.h) - center).RotateDeg((float) (associated.angleDeg))
                + center - Camera::pos;
        points[3] = {(int) point.x, (int) point.y};

        SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    }
}

bool Collider::Is(string type) {
    return type == COLLIDER_TYPE;
}

void Collider::SetScale(const Vec2 &scale) {
    this->scale = scale;
}

const Vec2 &Collider::GetScale() const {
    return scale;
}

void Collider::SetOffset(const Vec2 &offset) {
    this->offset = offset;
}

const Vec2 &Collider::GetOffset() const {
    return offset;
}

const Edge &Collider::GetEdge() const {
    return edge;
}

const Rect &Collider::GetBox() const {
    return box;
}

void Collider::SetEdge(const Edge &edge) {
    Collider::edge = edge;
}
