//
// Created by edgar on 07/06/18.
//

#ifndef SRC_ENEMY1_H
#define SRC_ENEMY1_H

#define PLAYER_DISTANCE_THRESHOLD 80
#define FCE_PLAYER_DISTANCE_OFFSET 300
#define IDLE_TIME 1
#define FCE_SPEED 200

#include "Enemy.h"

class FallingChasingEnemy : public Enemy {
public:
    explicit FallingChasingEnemy(GameObject &associated, int hp, Vec2 initialPosition, bool startFalling = true);

    void Update(float dt) override;

    void NotifyCollision(GameObject &other) override;

private:
    bool fell, landed, hit, playDeadByBulledSound;
    Vec2 speed;
    Timer idleTimer, preparingTimer, attackingTimer, deadTimer;
};


#endif //SRC_ENEMY1_H
