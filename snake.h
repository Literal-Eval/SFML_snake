#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "constants.h"

class Snake
{
private:
    std::vector<sf::Vector2f> bodyArray{sf::Vector2f{330, 240}};
    std::vector<sf::Vector2f> bodyArrayTemp{sf::Vector2f{330, 240}};
    sf::Vector2f movement{0, 0};
    std::vector<sf::Vector2f> movements{{0, 0}};

    sf::Sound moveSound;
    sf::SoundBuffer moveSoundBuffer;

public:
    Snake();

    void eat();
    void move();
    void setMovement(sf::Vector2f newMovement);
    bool checkEat(sf::Vector2f foodPos);
    sf::Vector2f &getHead();
    std::vector<sf::Vector2f> &getSnakeBody();
};

#endif