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

void Registry::AddEntityToSystems(Entity entity) {
    const auto entityId = entity.GetId();
    auto& entitySignature = entitySignatures[entityId];

    for (auto& system : systems) {
        const auto& sysSignature = system.second->GetSignature();

        if ((entitySignature & sysSignature) == sysSignature) {
            system.second->AddEntity(entity);
        }
    }
}

void Registry::DestroyEntity(Entity entity) {
}

void Registry::Update() {
}