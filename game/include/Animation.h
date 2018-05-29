//
// Created by edgar on 25/05/18.
//

#ifndef SRC_ANIMATION_H
#define SRC_ANIMATION_H

#define ANIMATION_TYPE "Animation"


#include "Component.h"
#include "Timer.h"

class Animation : public Component {
public:
    void Render() override;
    bool Is(string type) override;

    virtual void onAnimationUpdate(float dt) = 0;

protected:
    //Only Animation subclasses must instatiate it
    explicit Animation(GameObject &associated, float duration, ActionCallback onAnimationEnd = nullptr, float startOffset = 0);

    float startOffset;
    float duration;

    ActionCallback onAnimationEnd;

private:
    //Update(dt) must be private so that Animation's subclasses won't be able to override it
    void Update(float dt) override;
    Timer timer;

};


#endif //SRC_ANIMATION_H
