#pragma once

class Entity {
    int id;
public:
    explicit Entity(const int id) : id(id){};

    int GetId() const;

    bool operator<(const Entity& other) const {
        return id < other.id;
    }

    bool operator==(const Entity& other) const {
        return id == other.id;
    }
};