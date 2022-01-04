#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <SFML/Graphics.hpp>
#include "constants.h"

class Assets {
 public:
  sf::RectangleShape body{sf::Vector2f{blockWidth, blockHeight}};
  sf::RectangleShape grassLight{sf::Vector2f{blockWidth, blockHeight}};
  sf::RectangleShape grassDark{sf::Vector2f{blockWidth, blockHeight}};
  sf::RectangleShape borderLight{sf::Vector2f{blockWidth, blockHeight}};
  sf::RectangleShape borderDark{sf::Vector2f{blockWidth, blockHeight}};

  Assets();
  // ~Assets();
};

#endif