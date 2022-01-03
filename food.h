#ifndef _FOOD_H_
#define _FOOD_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "constants.h"

class Food
{
private:
    sf::Sprite body;
    sf::Vector2f position{120, 120};

public:
    Food();

    void move(bool checkMove);
    sf::Sprite &getBody();
    sf::Vector2f &getPosition();
};

#endif