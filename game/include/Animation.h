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
    Animation(GameObject &associated);
    Animation(GameObject &associated, float duration);
    Animation(GameObject &associated, float duration, float startOffset);
    Animation(GameObject &associated, float duration, ActionCallback &onAnimationEnd);
    Animation(GameObject &associated, float duration, float startOffset, ActionCallback &onAnimationEnd);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    virtual void onAnimate(float dt) = 0;

protected:
    float startOffset;
    float duration;
    Timer timer;

    ActionCallback onAnimationEnd;

};


#endif //SRC_ANIMATION_H