#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>


class AssetStore {
    std::map<std::string, SDL_Texture*> textures;
    SDL_Renderer* renderer;

    void ClearTextures();

public:
    explicit AssetStore(SDL_Renderer* renderer);
    ~AssetStore();
    void AddTexture(const std::string& textureName, const std::string& texturePath);
    SDL_Texture *GetTexture(const std::string& textureName);
};

