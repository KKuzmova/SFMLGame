//
// Created by Mac on 2022-02-20.
//

#ifndef BLUEBOX_GAME_H
#define BLUEBOX_GAME_H

#include <iostream>
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Cubes.h"


class Game {
private:
    //variables

    //window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event{};

    //game logic
    bool whileJump;
    bool whileMove;
    bool rMove;
    bool lMove;
    bool falling;

    float jumpF;          //force in Newton (kg*m/s^2)
    float mass;          //mass in kg

    float posX;
    bool coll;

    //game objects
    Player player;
    std::vector<Cubes> cubes;
    std::vector<Cubes> cubes2;
    std::vector<Cubes> cubes3;
    std::vector<Cubes> cubes4;
    sf::RectangleShape cube;

    //resources
    sf::Font font;
    sf::Text levelText;
    sf::Texture KeyArrowTexture;
    sf::Sprite rightKeyArrow;
    sf::Sprite leftKeyArrow;
    sf::Music soundtrack;

    //levels
    unsigned numOfBlueCubes[4] = {1, 2, 3, 4};
    std::vector<std::vector<Cubes>> levels;
    unsigned current_lvl = 0;

    bool thread_end_running = false;
    sf::Thread end_t = sf::Thread(&Game::end, this);

    //private functions
    void initVariables();

    void initWindow();

    void initMusic();

    void initSprites();

    void initFonts();

    void initText();

    void initCubes();

public:
    // constructors / destructors
    Game();

    virtual ~Game();

    //accessors
    const bool running() const;

    //functions
    void pollEvents();

    void end();

    void movement(float &deltaTime);

    void update(float *deltaTime);

    void renderSprites();

    void renderText();

    void render();
};


#endif //BLUEBOX_GAME_H
