//
// Created by edgar on 29/05/18.
//

#include <engine/components/Sprite.h>
#include <engine/components/Sound.h>
#include <engine/components/Text.h>
#include <player/Player.h>
#include <engine/components/animation/LineTween.h>
#include <engine/Game.h>
#include <engine/components/events/PeriodicEvent.h>
#include "crate/LifeCrate.h"

LifeCrate::LifeCrate(GameObject &associated, const Vec2 &initialPosition, int health, bool startFalling) :
        Crate(associated, initialPosition, startFalling), health(health) {
    Sprite* lifeCrateImg = new Sprite(associated, "img/life_crate.png");
    associated.AddComponent(lifeCrateImg);

    if(startFalling) {
        associated.box.y = -3*associated.box.h;
    } else{
        associated.box.y = initialPosition.y;
    }
}

void LifeCrate::onCatch() {
    associated.RequestDelete();

    auto catchGO(new GameObject);
    auto recharge(new Sound(*catchGO, "audio/recarregar.ogg"));
    recharge->Play();
    catchGO->AddComponent(recharge);
    Text *text = new Text(*catchGO, "font/Japanese.ttf", 30, Text::BLENDED, "+" + to_string(health), {255, 255, 255, 255});
    catchGO->AddComponent(text);
    catchGO->AddComponent(new LineTween(*catchGO, 1.5,
                                        associated.box.GetCenter() - catchGO->box.GetCenter(),
                                        associated.box.GetCenter() - catchGO->box.GetCenter() + Vec2(0, -50),
                                        [catchGO] {catchGO->RequestDelete();} ));

    catchGO->AddComponent(new PeriodicEvent(*catchGO, 0.1,
                                             [text] {text->SetAlpha(0);},
                                             [text] {text->SetAlpha(255);}, 0.1, 0.5));

    Player::player->SetHp(Player::player->GetHp() + health);

    Game::GetInstance().GetCurrentState().AddObject(catchGO);

}