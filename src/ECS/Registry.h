#pragma once

#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <utility>
#include <memory>
#include "Entity.h"
#include "System.h"
#include "Component.h"
#include "ComponentsList.h"
#include "../Logger.h"

class Registry {
private:
    int numOfEntities = 0;
    std::vector<std::unique_ptr<BaseComponentList>> componentLists;
    std::vector<Signature> entitySignatures;
    std::unordered_map<std::type_index, std::unique_ptr<System>> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesRemoved;

    Logger* logger;

public:
    explicit Registry(Logger* logger)
    : logger(logger){}

    Entity CreateEntity();

    template <typename T, typename ...TArgs>
    void AddComponent(Entity entity, TArgs&& ...args);

    template <typename TComponent>
    void RemoveComponent(Entity entity);

    template <typename TComponent>
    TComponent& GetComponent(Entity entity);

    template <typename T>
    bool HasCmponent(Entity entity);

    void DestroyEntity(Entity entity);
    void AddEntityToSystem(Entity entity);


    template <typename TSystem, typename ...TArgs>
    void AddSystem(TArgs&& ...args);

    template <typename TSystem>
    bool HasSystem();

    template <typename TSystem>
    TSystem& GetSystem();

    template <typename TSystem>
    bool RemoveSystem();

    void AddEntityToSystems(Entity entity);

    void Update();

    Logger& GetLogger(){return *logger;}
};

template<typename T, typename ... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args) {
    const auto componentId = Component<T>::GetID();
    const auto entityId = entity.GetId();

    if (componentId>=componentLists.size()) {
        componentLists.resize(componentLists.size()+1);
    }

    if (!componentLists[componentId]) {
        componentLists[componentId] = std::make_unique<ComponentsList<T>>(numOfEntities);
    }

    auto* componentList = static_cast<ComponentsList<T>*>(componentLists[componentId].get());
    if (entityId>=componentList->Size()) {
        componentList->Resize(numOfEntities);
    }

    T newComponent(std::forward<TArgs>(args)...);

    componentList->Set(entityId, newComponent);

    entitySignatures[entityId].set(componentId);
}

template<typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetID();
    const auto entityId = entity.GetId();

    entitySignatures[entityId].reset(componentId);
}

template<typename TComponent>
TComponent& Registry::GetComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetID();
    const auto entityId = entity.GetId();

    auto* componentList = static_cast<ComponentsList<TComponent>*>(componentLists[componentId].get());

    return componentList->Get(entityId);
}

template<typename T>
bool Registry::HasCmponent(Entity entity) {
    const auto componentId = Component<T>::GetID();
    const auto entityId = entity.GetId();

    return entitySignatures[entityId].test(componentId);
}

template<typename TSystem, typename ... TArgs>
void Registry::AddSystem(TArgs &&...args) {
    auto system = std::make_unique<TSystem>(this, std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), std::move(system)));
}

template<typename TSystem>
bool Registry::HasSystem() {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template<typename TSystem>
TSystem& Registry::GetSystem() {
    auto& system = systems[std::type_index(typeid(TSystem))];
    return *(static_cast<TSystem*>(system.get()));
}
