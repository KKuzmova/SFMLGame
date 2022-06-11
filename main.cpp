#include "Game.h"

int main() {
    
    //initialize "game engine"
    Game *game = new Game;

    float deltaTime;
    sf::Clock clock;

    //game loop
    while (game->running()) {

        deltaTime = clock.restart().asSeconds();

        //updating
        game->update(&deltaTime);

        //rendering
        game->render();
    }

    return 0;
}
