#include "assets.h"

Assets::Assets() {
  body.setFillColor(sf::Color::White);
  grassLight.setFillColor(sf::Color(lightGreen));
  grassDark.setFillColor(sf::Color(darkGreen));
  borderLight.setFillColor(sf::Color(innerBorderColor));
  borderDark.setFillColor(sf::Color(outerBorderColor));
}