#ifndef PLAYER_H
#define PLAYER_H

#include "engine/Vec2.h"
#include "PlayerArms.h"
#include "engine/Component.h"
#include "engine/components/Sprite.h"
#include "BodyState.h"

#define PLAYER_SPEED  300
#define JUMP_SPEED    500
#define GRAVITY       50.0f
#define PLAYER_T "Player"
#define PLAYER_MAX_LIVES 5

class Player : public Component {
public:
    Player(GameObject& associated);
    ~Player();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    static Player* player;
    static PlayerArms* playerArms;

    int GetHp() const;
    void SetHp(int hp);
    void IncremmentHp();
    void DecrementHp();

    MoveState getMovementState() const;

private:

    BodyState *bodyState;

    MoveState movementState;
    JumpState jumpState;

    Vec2 speed;
    float verticalSpeed;
    float horizontalSpeed;
    int hp;

};


#endif // PLAYER_H