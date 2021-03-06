//
// Created by edgar on 04/07/18.
//

#include <Gravity.h>
#include <Sprite.h>
#include <Bullet.h>
#include <CollisionTile.h>
#include <Camera.h>
#include <Player.h>
#include <Game.h>
#include <Sound.h>
#include <Collider.h>
#include "BigGuy.h"

BigGuy::BigGuy(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance) : Enemy(associated, hp, initialPosition) {

    this->going = true;
    this->initialPosition = initialPosition;
    this->maxDistance = maxDistance;
    this->damaged = false;
    this->canDamage = true;

    walking = StaticSprite("img/enemy/BigGuy/walking.png", 6, 0.1f);
    attacking = StaticSprite("img/enemy/BigGuy/attack.png", 9, 0.1f);
    deadByBullet = StaticSprite("img/enemy/BigGuy/death.png", 5, 0.1f);

    state = E_WALKING;

    Sprite* img = new Sprite(associated, walking.sprite, walking.frameCount, walking.frameTime);

    walkSound = new Sound(associated, "audio/enemy/BigGuy/passos1.mp3");
    explosionSound = new Sound(associated, "audio/enemy/BigGuy/explosion1.mp3");

    associated.orientation = RIGHT;
    associated.AddComponent(img);
    associated.AddComponent(new Gravity(associated));
}

void BigGuy::Update(float dt) {

    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if(Player::player && IsCloseEnoughToPlayer(700)) {
        auto playerBox = Player::player->GetAssociatedBox();

        if (state == E_WALKING) {
            canDamage = true;
            attackCooldown.Update(dt);
            if(!walkSound->IsSoundPlaying()){
                walkSound->Play();
            }
            if (going) {
                if (collider->box.x < maxDistance + initialPosition.x) {
                    associated.orientation = RIGHT;
                    collider->box.x += BG_SPEED * dt;
                } else {
                    going = false;
                }

            } else {
                if (collider->box.x > initialPosition.x) {
                    associated.orientation = LEFT;
                    collider->box.x -= BG_SPEED * dt;
                } else going = true;
            }

            if (IsCloseEnoughToPlayer(BG_PLAYER_DISTANCE_OFFSET)) {
                if (attackCooldown.Get() > 3)
                    state = E_ATTACKING;
            }
        } else if (state == E_ATTACKING) {
            associated.orientation = playerBox.x < collider->box.x ? LEFT : RIGHT;
            going = associated.orientation != LEFT;
            attackingTimer.Update(dt);

            if (attackingTimer.Get() > (attacking.frameCount * attacking.frameTime) * (5.0F / 9.0F)) {
                Camera::Wiggle(0.2);
                damaged = canDamage;
                if(!explosionSound->IsSoundPlaying()){
                    explosionSound->Play(1);
                }
            }
            if (attackingTimer.Get() > attacking.frameCount * attacking.frameTime) {
                state = E_WALKING;
                attackCooldown.Restart();
                attackingTimer.Restart();
            }
        } else if (state == E_DEAD_BY_BULLET) {
            deadTimer.Update(dt);
            if (deadTimer.Get() > deadByBullet.frameCount * deadByBullet.frameTime) {
                associated.RequestDelete();
            }
        }

        if (hp <= 0) {
            state = E_DEAD_BY_BULLET;
        }

        // Atualiza box com box do collider
        auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
        associated.box.x = collider->GetBox().GetCenter().x - (collider->GetBox().w / collider->GetScale().x) / 2 + offset.x;
        associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;
    }
}

void BigGuy::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if (collisionTile) {
        Gravity *gravity = (Gravity*)associated.GetComponent(GRAVITY_TYPE);
        if(gravity){
            gravity->SetVerticalSpeed(0);
        }
        collider->box.y = other.box.y - collider->box.h;
        auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
        associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;
    }

    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }

    auto player = (Player*)other.GetComponent(PLAYER_TYPE);
    if(player && state == E_ATTACKING && damaged){
        player->DecrementHp();
        if(player->GetHp() <= 0) state = E_WALKING;
        canDamage = false;
    }
}
