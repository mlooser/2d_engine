#pragma once

#include "BaseComponent.h"

template<typename T>
class Component: public BaseComponent {
public:
    static int GetID() {
        static auto id = nextID++;
        return id;
    }
};