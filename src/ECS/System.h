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

protected:
    class Registry* owner;

public:
    explicit System(Registry* owner):owner(owner){}

    virtual ~System()= default;
    virtual void Update(float deltaTime) { (void)deltaTime; }

    template <typename T> void RequireComponent();

    void AddEntity(Entity entity);
    Signature& GetSignature() { return requiredSignature; }
    const std::vector<Entity>& GetEntities() const { return entities; }
    size_t GetEntityCount() const { return entities.size(); }
};

template<typename T>
void System::RequireComponent() {
    auto componentId = Component<T>::GetID();
    requiredSignature.set(componentId);
}