//
// Created by Mac on 2022-02-21.
//

#ifndef BLUEBOX_PLAYER_H
#define BLUEBOX_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    //objects
    sf::RectangleShape mainCube;

    //functions
    void initSprite();

public:
    //variables
    float speedValue = 0.f;

    //constructors / destructors
    Player();

    virtual ~Player();

    //accessors
    const sf::RectangleShape &getShape() const;

    //functions

    void playerMove(bool rMove, bool lMove);

    void setPos(float x, float y);

    void jump(float deltaTime);

    void render(sf::RenderTarget *target);

};


#endif //BLUEBOX_PLAYER_H
