//
// Created by edgar on 31/05/18.
//

#include <Game.h>
#include <CameraFollower.h>
#include <Sprite.h>
#include <LifeManager.h>
#include <GunManager.h>
#include "MenuHUD.h"

MenuHUD::MenuHUD(GameObject &associated, bool isFace, bool isLifeIndicator, bool isClock) :
        Component(associated) {

    this->isClock = isClock;
    this->isFace = isFace;

    if(isFace){
        AddFace();
    }

    if(isLifeIndicator){
        AddLifeIndicator();
    }

    if(isClock){
        AddClock();
    }

    auto gunIcon(new GameObject());
    gunIcon->AddComponent(new GunManager(*gunIcon, {GAME_WIDTH - gunIcon->box.w - MARGIN_LEFT, MARGIN_TOP}));
    Game::GetInstance().GetCurrentState().AddObject(gunIcon);


}

void MenuHUD::Update(float dt) {
    if(isClock) {
        clock->Update(dt);
        Text *clockText = (Text*)(clockGO->GetComponent(TEXT_TYPE));
        if(clockText) clockText->SetText(clock->GetMinutesString() + ":" + clock->GetSecondsString());
    }

    if(isFace) {
    }
}

void MenuHUD::Render() {

}

bool MenuHUD::Is(string type) {
    return type == MENU_HUD_TYPE;
}

void MenuHUD::AddFace() {
    faceGO = new GameObject();
    faceGO->AddComponent(new Sprite(*faceGO, "img/hud.png"));
    faceGO->AddComponent(new CameraFollower(*faceGO, {MARGIN_LEFT, MARGIN_TOP}));
    Game::GetInstance().GetCurrentState().AddObject(faceGO);
}

void MenuHUD::AddLifeIndicator() {
    new LifeManager({MARGIN_LEFT, 0});
    LifeManager::Update();
}

void MenuHUD::AddClock() {
    clockGO = new GameObject();
    clockGO->AddComponent(new Text(*clockGO, "font/Japanese.ttf", 80, Text::BLENDED, "00:00", {255, 255, 255, 255}));
    clockGO->AddComponent(new CameraFollower(*clockGO, Vec2((GAME_WIDTH/2) - clockGO->box.w/2, MARGIN_TOP)));

    clock = new Clock();

    Game::GetInstance().GetCurrentState().AddObject(clockGO);
}
