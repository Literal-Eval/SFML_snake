#include "food.h"

Food::Food() {
  sf::Texture* bodyTexture = new sf::Texture();
  if (!bodyTexture->loadFromFile("./assets/images/apple.png")) {
    std::cout << sf::err;
  } else {
    bodyTexture->setSmooth(true);
    body.setTexture(*bodyTexture);
    body.scale(((double)blockWidth / bodyTexture->getSize().x) * 1.5,
               ((double)blockHeight / bodyTexture->getSize().y) * 1.5);
  }
};

void Food::move(bool checkMove) {
  if (!checkMove)
    return;

  position.x = (std::rand() % screenWidth / blockWidth) * blockWidth;
  position.y = (std::rand() % screenHeight / blockHeight) * blockHeight;
  body.setPosition(position.x - 8, position.y - 8);
}

sf::Sprite& Food::getBody() {
  return body;
}

sf::Vector2f& Food::getPosition() {
  return position;
}