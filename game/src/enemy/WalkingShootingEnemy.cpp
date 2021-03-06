//
// Created by edgar on 14/06/18.
//

#include <Sprite.h>
#include <Gravity.h>
#include <CollisionTile.h>
#include <Bullet.h>
#include <Sound.h>
#include <Game.h>
#include <Player.h>
#include <Collider.h>
#include "WalkingShootingEnemy.h"

WalkingShootingEnemy::WalkingShootingEnemy(GameObject &associated, int hp, Vec2 initialPosition) : Enemy(associated, hp, initialPosition) {
    falling = StaticSprite("img/enemy_falling.png", 2, 0.3f);
    chasing = StaticSprite("img/enemy_running.png", 12, 0.06f);
    idle = StaticSprite("img/enemy_idle.png", 6, 0.2f);
    stopped = StaticSprite("img/enemy_idle.png", 6, 0.2f);
    preparing = StaticSprite("img/enemy_preparing.png", 4, 0.1f);
    attacking = StaticSprite("img/enemy_attacking.png", 8, 0.1f);
    deadByBullet = StaticSprite("img/enemy_dying_gun.png", 20, 0.1f, 2);

    state = E_STOPPED;

    Sprite* img = new Sprite(associated, falling.sprite, falling.frameCount, falling.frameTime);

    associated.orientation = RIGHT;
    associated.AddComponent(img);
    associated.AddComponent(new Gravity(associated));
}

void WalkingShootingEnemy::Update(float dt) {

    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if(Player::player) {
        auto playerBox = Player::player->GetAssociatedBox();

        if (state == E_STOPPED) {
            if (playerBox.x > collider->box.x - WSE_PLAYER_DISTANCE_OFFSET) {
                state = E_ATTACKING;
            }
        } else if (state == E_ATTACKING) {
            attackingTimer.Update(dt);
            if (attackingTimer.Get() > attacking.frameCount * attacking.frameTime) {
                int shootAngle = (associated.orientation != Orientation::LEFT ? 180 : 0);
                Shoot(shootAngle);
                state = E_IDLE;
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

void WalkingShootingEnemy::NotifyCollision(GameObject &other) {
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
}

void WalkingShootingEnemy::Shoot(float angle) {
    auto bulletGo = new GameObject;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 400, 1, 1000, "img/minionbullet2.png", 3, 0.01f, true));
    if(associated.orientation == Orientation::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w - bulletGo->box.w - 8;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8;
    } else {
        bulletGo->box.x = associated.box.GetPos().x + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h + 8;
    }
    auto sound(new Sound(*bulletGo, "audio/GUN SHOT.ogg"));
    sound->Play();
    bulletGo->AddComponent(sound);
    Game::GetInstance().GetCurrentState().AddCollisionObject(bulletGo);
}
