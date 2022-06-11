//
// Created by Mac on 2022-02-21.
//

#include "Cubes.h"

//private functions

void Cubes::initCubes(const sf::RenderWindow &window, sf::Vector2f position) {

    sf::Color color;
    switch (this->type) {
        case Starting:
            this->cube.setSize(sf::Vector2f(40.f, 40.f));
            color = sf::Color(160, 221, 0, 255);
            break;
        case Finishing:
            this->cube.setSize(sf::Vector2f(40.f, 40.f));
            color = sf::Color(249, 38, 68, 255);
            break;
        case SmallCollect:
            this->cube.setSize(sf::Vector2f(20.f, 20.f));
            color = sf::Color(166, 226, 228, 255);
            break;
    }
    this->cube.setFillColor(color);
    this->cube.setPosition(position);

}


// constructors / destructors
Cubes::Cubes(const sf::RenderWindow &window, int type, sf::Vector2f position)
        : type(type) {
    this->initCubes(window, position);
}

Cubes::~Cubes() {

}

const sf::RectangleShape &Cubes::getShape() const {
    return this->cube;
}

const sf::Color &Cubes::getColor() const {
    return this->cube.getFillColor();
}

const int &Cubes::getType() const {
    return this->type;
}

//public functions

void Cubes::setColor(sf::Color color) {
    this->cube.setFillColor(color);
}

void Cubes::setCubesSize(float x, float y) {
    this->cube.setSize(sf::Vector2f(x, y));
}

bool Cubes::getCollision(Player *player) {
    if (player->getShape().getGlobalBounds().intersects(this->cube.getGlobalBounds())) {
        return true;
    }
    return false;
}

void Cubes::render(sf::RenderTarget &target) {

    target.draw(this->cube);
}

