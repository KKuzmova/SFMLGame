//
// Created by Mac on 2022-02-21.
//

#include "Player.h"


void Player::initSprite() {

    this->mainCube.setSize(sf::Vector2f(10, 10));
    this->mainCube.setFillColor(sf::Color(15, 190, 208, 255));
    this->mainCube.setPosition(495, 270);

}

Player::Player() {

    this->initSprite();
}

Player::~Player() {

}

const sf::RectangleShape &Player::getShape() const {
    return this->mainCube;
}

void Player::playerMove(bool rMove, bool lMove) {
    if (rMove) {
        mainCube.move(79, 0);
    }
    if (lMove) {
        mainCube.move(-79, 0);
    }
}

void Player::setPos(float x, float y) {
    this->mainCube.setPosition(x, y);
}

void Player::jump(float deltaTime) {
    float gravityAcceleration = 17.5;

    this->speedValue -= gravityAcceleration * deltaTime;
    this->mainCube.move(0, -this->speedValue);
}


void Player::render(sf::RenderTarget *target) {
    target->draw(this->mainCube);
}
