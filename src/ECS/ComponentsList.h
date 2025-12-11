#pragma once

#include <vector>
#include "BaseComponent.h"

class BaseComponentList {
public:
    virtual ~BaseComponentList() = default;
};

template <typename T>
class ComponentsList: public BaseComponent {
private:
    std::vector<T> components;

public:
    ComponentsList(int initSize) {
        components.resize(initSize);
    }

    int Size();

    void Resize(int newSize);

    void Set(int index, T component);
};

template<typename T>
int ComponentsList<T>::Size() {
    return components.size();
}

template<typename T>
void ComponentsList<T>::Resize(int newSize) {
    components.resize(newSize);
}

template<typename T>
void ComponentsList<T>::Set(int index, T component) {
    components[index] = component;
}