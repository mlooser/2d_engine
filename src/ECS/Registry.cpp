#include "Registry.h"

Entity Registry::CreateEntity() {
    int newId = numOfEntities++;
    if (newId > entitySignatures.size()) {
        entitySignatures.resize(newId + 1);
    }

    Entity entity(newId);
    entitiesToBeAdded.insert(entity);
    return entity;
}

void Registry::DestroyEntity(Entity entity) {
}

void Registry::Update() {
}