#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "constants.h"

class Snake {
 private:
  std::vector<sf::Vector2f> bodyArray{sf::Vector2f{330, 240},
                                      sf::Vector2f{330 - blockWidth, 240}};
  std::vector<sf::Vector2f> bodyArrayTemp{sf::Vector2f{330, 240}};
  sf::Vector2f movement{0, 0};
  std::vector<sf::Vector2f> movements{{5, 0}, {5, 0}};

  sf::Sound moveSound;

  sf::Sprite head;
  sf::Sprite tail;

  sf::Sprite headRight;
  sf::Sprite headLeft;
  sf::Sprite headUp;
  sf::Sprite headDown;
  sf::Sprite tailRight;
  sf::Sprite tailLeft;
  sf::Sprite tailUp;
  sf::Sprite tailDown;
  sf::Sprite bodyHorizontal;
  sf::Sprite bodyVertical;

 public:
  Snake();

  void eat();
  void move();
  void setMovement(sf::Vector2f newMovement);
  bool checkEat(sf::Vector2f foodPos);

  std::vector<sf::Vector2f>& getSnakeBody();

  sf::Vector2f& getHeadPos();
  sf::Sprite& getHeadSprite();
  sf::Sprite& getTailSprite();
  sf::Sprite& getBodySprite(int index);
};

#endif