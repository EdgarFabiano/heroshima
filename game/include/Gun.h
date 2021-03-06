//
// Created by edgar on 25/05/18.
//

#ifndef GUN_H
#define GUN_H

#include <string>
#include "Structs.h"

using std::string;

class Gun {
public:

    Gun(int damage, int ammo, float cooldownTime, StaticSprite spriteRest, StaticSprite spriteWalk,
        StaticSprite spriteShoot, StaticSprite crouch, Projectile projectile);

    Gun();

    int getDamage() const;
    int getAmmo() const;
    void setAmmo(int ammo);
    int getFull() const;
    float getCooldownTime() const;
    void decrementAmmo();

    const StaticSprite &getSpriteRest() const;
    const StaticSprite &getSpriteWalk() const;
    const StaticSprite &getSpriteShoot() const;
    const StaticSprite &getSpriteCrouch() const;

    const Projectile &getProjectile() const;

private:
    int damage;
    int ammo;

    int full;
    float cooldownTime;

    StaticSprite rest, walk, shoot, crouch;
    Projectile projectile;

};


#endif //SRC_GUN_H
