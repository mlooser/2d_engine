#pragma once

#include <bitset>
#include <vector>
#include "Entity.h"
#include "Component.h"

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class System {
    Signature requiredSignature;
    std::vector<Entity> entities;

public:
    template <typename T> void RequireComponent();
};

template<typename T>
void System::RequireComponent() {
    auto componentId = Component<T>::GetID();
    requiredSignature.set(componentId);
}