//
// Created by Mac on 2022-02-21.
//

#ifndef BLUEBOX_CUBES_H
#define BLUEBOX_CUBES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

enum CubesTypes {
    Starting = 0, Finishing, SmallCollect
};

class Cubes {
private:
    //variables
    sf::RectangleShape cube;
    int type;

    //functions

    void initCubes(const sf::RenderWindow &window, sf::Vector2f vector2);

public:
    // constructors / destructors
    Cubes(const sf::RenderWindow &window, int type, sf::Vector2f position);

    virtual ~Cubes();

    //accessors
    const sf::RectangleShape &getShape() const;

    const sf::Color &getColor() const;

    const int &getType() const;

    //functions

    void setColor(sf::Color color);

    void setCubesSize(float x, float y);

    bool getCollision(Player *player);

    void render(sf::RenderTarget &target);
};


#endif //BLUEBOX_CUBES_H
