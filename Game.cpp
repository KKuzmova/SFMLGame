//
// Created by Mac on 2022-02-20.
//

#include "Game.h"

//private functions

void Game::initVariables() {
    this->window = nullptr;

    //game logic
    this->whileJump = false;
    this->whileMove = false;
    this->rMove = false;
    this->lMove = false;
    this->falling = true;

    this->jumpF = 400;
    this->mass = 45;

    this->posX = 0;
    this->coll = false;
}

void Game::initWindow() {

    this->videoMode.height = 576;
    this->videoMode.width = 1088;
    this->window = new sf::RenderWindow(this->videoMode, "BlueBox", sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(60);
}

void Game::initMusic() {
    soundtrack.openFromFile("sounds/soundtrack.ogg");
    soundtrack.play();
    soundtrack.setLoop(true);
}

void Game::initSprites() {
    this->KeyArrowTexture.loadFromFile("images/keyboard_arrow.png");

    this->rightKeyArrow.setTexture(KeyArrowTexture);
    this->rightKeyArrow.setPosition(100, 100);
    this->rightKeyArrow.setScale(.25, .25);

    this->leftKeyArrow.setTexture(KeyArrowTexture);
    this->leftKeyArrow.setPosition(300, 100);
    this->leftKeyArrow.setScale(-.25, .25);
}

void Game::initFonts() {
    this->font.loadFromFile("fonts/prompt-medium.ttf");
}

void Game::initText() {
    this->levelText.setFont(this->font);
    this->levelText.setCharacterSize(24);
    this->levelText.setFillColor(sf::Color(146, 222, 0, 255));
    this->levelText.setPosition(50, 110);
    this->levelText.setString("Use         and          to move.");
}

void Game::initCubes() {

    //level 1
    this->cubes.emplace_back(*this->window, Starting, sf::Vector2f(480, 320));
    this->cubes.emplace_back(*this->window, SmallCollect, sf::Vector2f(570, 320)); //small:570 large:540 medium:560
    this->cubes.emplace_back(*this->window, Finishing, sf::Vector2f(640, 320)); // 640

    //level 2
    this->cubes2.emplace_back(*this->window, Starting, sf::Vector2f(480, 320));
    this->cubes2.emplace_back(*this->window, SmallCollect, sf::Vector2f(570, 320)); //small:570 large:540 medium:560
    this->cubes2.emplace_back(*this->window, SmallCollect, sf::Vector2f(640, 320));
    this->cubes2.emplace_back(*this->window, Finishing, sf::Vector2f(710, 320));

    //level 3
    this->cubes3.emplace_back(*this->window, Starting, sf::Vector2f(480, 320));
    this->cubes3.emplace_back(*this->window, SmallCollect, sf::Vector2f(570, 320)); //small:570 large:540 medium:560
    this->cubes3.emplace_back(*this->window, SmallCollect, sf::Vector2f(640, 320));
    this->cubes3.emplace_back(*this->window, SmallCollect, sf::Vector2f(800, 320));
    this->cubes3.emplace_back(*this->window, Finishing, sf::Vector2f(710, 320));

    //level 4
    this->cubes4.emplace_back(*this->window, Starting, sf::Vector2f(480, 320));
    this->cubes4.emplace_back(*this->window, SmallCollect, sf::Vector2f(410, 320));
    this->cubes4.emplace_back(*this->window, SmallCollect, sf::Vector2f(570, 320)); //small:570 large:540 medium:560
    this->cubes4.emplace_back(*this->window, SmallCollect, sf::Vector2f(640, 320));
    this->cubes4.emplace_back(*this->window, SmallCollect, sf::Vector2f(800, 320));
    this->cubes4.emplace_back(*this->window, Finishing, sf::Vector2f(710, 320));

    this->cube.setSize(sf::Vector2f(40.f, 40.f));
    this->cube.setPosition(480, 320);

    this->levels.push_back(cubes);
    this->levels.push_back(cubes2);
    this->levels.push_back(cubes3);
    this->levels.push_back(cubes4);
}

//public functions

//constructors / destructors
Game::Game() {

    this->initVariables();
    this->initWindow();
    this->initMusic();
    this->initSprites();
    this->initFonts();
    this->initText();
    this->initCubes();

}

Game::~Game() {
    delete this->window;
}

//accessors
const bool Game::running() const {
    return this->window->isOpen();
}

//functions
void Game::pollEvents() {

    //polling
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}


void Game::movement(float &deltaTime) {
    this->coll = false;
    for (size_t i = 0; i < this->levels[current_lvl].size(); i++) {
        if (this->player.getShape().getGlobalBounds().intersects(
                this->levels[current_lvl][i].getShape().getGlobalBounds())) {
            switch (this->levels[current_lvl][i].getType()) {

                case CubesTypes::Starting:
                    if (levels[current_lvl][i + 1].getColor() == sf::Color::Transparent) {
                        this->levels[current_lvl][i + 1].setCubesSize(0, 0);
                    }
                    if (levels[current_lvl][i + 2].getColor() == sf::Color::Transparent) {
                        this->levels[current_lvl][i + 2].setCubesSize(0, 0);
                    }
                    this->posX = levels[current_lvl][i].getShape().getPosition().x;
                    break;

                case CubesTypes::Finishing:
                    if (levels[current_lvl][i - 1].getColor() == sf::Color::Transparent) {
                        this->levels[current_lvl][i - 1].setCubesSize(0, 0);
                    }
                    if (levels[current_lvl][i - 2].getColor() == sf::Color::Transparent) {
                        this->levels[current_lvl][i - 2].setCubesSize(0, 0);
                    }
                    this->posX = levels[current_lvl][i].getShape().getPosition().x;
                    break;

                case CubesTypes::SmallCollect:
                    if (levels[current_lvl][i - 1].getColor() == sf::Color::Transparent) {
                        this->levels[current_lvl][i - 1].setCubesSize(0, 0);
                    }
                    if (levels[current_lvl][i].getColor() != sf::Color::Transparent) {
                        if (this->numOfBlueCubes[current_lvl] != 0) {
                            this->numOfBlueCubes[current_lvl] -= 1;
                        }
                        this->posX = levels[current_lvl][i].getShape().getPosition().x;
                        levels[current_lvl][i].setColor(sf::Color::Transparent);
                        whileJump = false;
                    }
                    break;
            }
            this->coll = true;
        }
    }

    if (coll && !whileJump) {
        player.speedValue = jumpF / mass;
        whileJump = true;
        falling = false;
    }
    if (whileJump) {
        player.jump(deltaTime);
        if (player.getShape().getPosition().y > 320 - 9.5) {
            player.setPos(player.getShape().getPosition().x, 320 - 9.5);
            whileJump = false;
        }
    }
    if (!whileJump && falling) {
        player.jump(deltaTime);
    }

    if (player.getShape().getGlobalBounds().top + player.getShape().getGlobalBounds().height >=
        (float) this->window->getSize().y) {
        player.setPos(cube.getPosition().x + 12, cube.getPosition().y - 50);
        numOfBlueCubes[current_lvl] = current_lvl;
        for (size_t i = 0; i < this->levels[current_lvl].size(); i++) {
            if (this->levels[current_lvl][i].getType() == SmallCollect) {
                this->levels[current_lvl][i].setColor(sf::Color(166, 226, 228, 255));
                this->levels[current_lvl][i].setCubesSize(20.f, 20.f);
                this->numOfBlueCubes[current_lvl] = current_lvl + 1;
            }
        }
    }

    if (!falling) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !whileMove) {
            whileMove = true;
            rMove = true;
            lMove = false;
            falling = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !whileMove) {
            whileMove = true;
            lMove = true;
            rMove = false;
            falling = false;
        }
        if (whileMove) {
            player.playerMove(rMove, lMove);
            if (rMove) {
                if (player.getShape().getPosition().x > posX + 20) {
                    whileMove = false;
                    rMove = false;
                    lMove = false;
                    falling = true;
                }
            }
            if (lMove) {
                if (player.getShape().getPosition().x < posX - 20) {
                    whileMove = false;
                    rMove = false;
                    lMove = false;
                    falling = true;

                }
            }

        }
    }
}

void Game::update(float *deltaTime) {
    if (levels.capacity() <= current_lvl) {
        end_t.wait();
        thread_end_running = false;
        this->window->close();
        return;
    }

    this->pollEvents();
    this->movement(*deltaTime);

}

void Game::renderSprites() {
    this->window->draw(this->rightKeyArrow);
    this->window->draw(this->leftKeyArrow);
}

void Game::renderText() {
    this->window->draw(this->levelText);
}

void Game::end() {
    while (this->running()) {
        if (this->levels[current_lvl][levels[current_lvl].size() - 1].getCollision(&this->player) &&
            numOfBlueCubes[current_lvl] == 0) {
            if (current_lvl >= levels.capacity() - 1) {
                this->window->close(); // app end
                return;
            }

            current_lvl++;
            player.setPos(cube.getPosition().x + 12, cube.getPosition().y - 50);
        }
    }
}

void Game::render() {

    this->window->clear(sf::Color(235, 244, 246, 255));

    this->player.render(this->window);

    if (!thread_end_running) {
        thread_end_running = true;
        end_t.launch();
    }

    for (size_t i = 0; i < levels[current_lvl].size(); i++) {
        levels[current_lvl][i].render(*this->window);
    }

    this->renderSprites();
    this->renderText();

    this->window->display();
}
