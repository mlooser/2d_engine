#include "AssetStore.h"

#include <SDL2/SDL_image.h>

AssetStore::AssetStore(SDL_Renderer* renderer) : renderer(renderer) {
    AddTexture("tank", "./assets/images/tank-panther-left.png");
    AddTexture("tilemap-image", "./assets/tilemaps/jungle.png");
    AddTexture("chopper", "./assets/images/chopper.png");
}

AssetStore::~AssetStore() {
    ClearTextures();
}

void AssetStore::AddTexture(const std::string &textureName, const std::string &texturePath) {
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(textureName, texture);

}

SDL_Texture* AssetStore::GetTexture(const std::string &textureName) {
    return textures[textureName];
}

void AssetStore::ClearTextures() {
    for (const auto& tex : textures) {
        SDL_DestroyTexture(tex.second);
    }
}
