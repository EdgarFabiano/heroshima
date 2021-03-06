

//
// Created by edgar on 23/03/18.
//

#ifndef COMPONENT_CLASS
#define COMPONENT_CLASS

#include <iostream>
#include <functional>
#include "GameObject.h"

using namespace std;

class GameObject;

typedef function<void()> ActionCallback;

class Component {
public:
    Component(GameObject& associated);
    virtual ~Component();

    virtual void Start();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;

    virtual void NotifyCollision(GameObject& other);

    Rect GetAssociatedBox();

protected:
    GameObject& associated;

};


#endif //SRC_COMPONENT_H
