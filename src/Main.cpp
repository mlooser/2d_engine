#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>


int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    glm::vec2 velocity(0.0f, 0.0f);

    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Deps are fine" << std::endl;
    return 0;
}
