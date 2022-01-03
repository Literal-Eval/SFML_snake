#include "snake.h"

Snake::Snake() {
  sf::Texture* headRightTexture = new sf::Texture;
  sf::Texture* headLeftTexture = new sf::Texture;
  sf::Texture* headUpTexture = new sf::Texture;
  sf::Texture* headDownTexture = new sf::Texture;
  sf::Texture* tailRightTexture = new sf::Texture;
  sf::Texture* tailLeftTexture = new sf::Texture;
  sf::Texture* tailUpTexture = new sf::Texture;
  sf::Texture* tailDownTexture = new sf::Texture;
  sf::Texture* bodyHorizontalTexture = new sf::Texture;
  sf::Texture* bodyVerticalTexture = new sf::Texture;
  sf::SoundBuffer* moveSoundBuffer = new sf::SoundBuffer;

  if (!moveSoundBuffer->loadFromFile("assets/music/move.wav") ||
      !headRightTexture->loadFromFile("assets/images/head_right.png") ||
      !headLeftTexture->loadFromFile("assets/images/head_left.png") ||
      !headUpTexture->loadFromFile("assets/images/head_up.png") ||
      !headDownTexture->loadFromFile("assets/images/head_down.png") ||
      !tailRightTexture->loadFromFile("assets/images/tail_left.png") ||
      !tailLeftTexture->loadFromFile("assets/images/tail_right.png") ||
      !tailUpTexture->loadFromFile("assets/images/tail_down.png") ||
      !bodyHorizontalTexture->loadFromFile(
          "assets/images/body_horizontal.png") ||
      !bodyVerticalTexture->loadFromFile("assets/images/body_vertical.png") ||
      !tailDownTexture->loadFromFile("assets/images/tail_up.png")) {
    std::cout << sf::err;
  } else {
    moveSound.setBuffer(*moveSoundBuffer);

    headRight.setTexture(*headRightTexture);
    headLeft.setTexture(*headLeftTexture);
    headUp.setTexture(*headUpTexture);
    headDown.setTexture(*headDownTexture);
    tailRight.setTexture(*tailRightTexture);
    tailLeft.setTexture(*tailLeftTexture);
    tailUp.setTexture(*tailUpTexture);
    tailDown.setTexture(*tailDownTexture);

    bodyHorizontal.setTexture(*bodyHorizontalTexture);
    bodyVertical.setTexture(*bodyVerticalTexture);
  }
};

void Snake::eat() {
  auto bodyLast = bodyArray[bodyArray.size() - 1];
  auto movementLast = movements[movements.size() - 1];
  bodyLast += sf::Vector2f((movementLast.x / 5) * blockWidth * -1,
                           (movementLast.y / 5) * blockHeight * -1);
  bodyArray.push_back(bodyLast);
  movements.push_back(movementLast);
  bodyArrayTemp = bodyArray;
}

void Snake::move() {
  for (size_t i{0}; i < bodyArray.size(); i++) {
    bodyArray[i] += movements[i];
  }
}

void Snake::setMovement(sf::Vector2f newMovement) {
  if (newMovement != movements[0])
    moveSound.play();
  movements.insert(movements.begin(), newMovement);
  movements.pop_back();
}

bool Snake::checkEat(sf::Vector2f foodPos) {
  auto headPos{bodyArray[0]};
  auto tempPos{headPos + movement};

  if ((tempPos.x == foodPos.x) &&
          ((tempPos.y > foodPos.y && tempPos.y < foodPos.y + blockHeight) ||
           (tempPos.y + blockHeight > foodPos.y && tempPos.y < foodPos.y)) ||
      (tempPos.y == foodPos.y) &&
          ((tempPos.x > foodPos.x && tempPos.x < foodPos.x + blockWidth) ||
           (tempPos.x + blockWidth > foodPos.x && tempPos.x < foodPos.x))) {
    eat();
    return true;
  }
  return false;
}

sf::Vector2f& Snake::getHeadPos() {
  return bodyArray[0];
}

sf::Sprite& Snake::getHeadSprite() {
  if (movements[0].x == 5) {
    return headRight;
  } else if (movements[0].x == -5) {
    return headLeft;
  } else if (movements[0].y == -5) {
    return headUp;
  } else {
    return headDown;
  }
}

sf::Sprite& Snake::getTailSprite() {
  if (movements[movements.size() - 1].x == 5) {
    return tailRight;
  } else if (movements[movements.size() - 1].x == -5) {
    return tailLeft;
  } else if (movements[movements.size() - 1].y == -5) {
    return tailUp;
  } else {
    return tailDown;
  }
}

sf::Sprite& Snake::getBodySprite(int index) {
  if (index == 0)
    return getHeadSprite();
  else if (index == bodyArray.size() - 1)
    return getTailSprite();
  else {
    if (movements[index].x) {
      return bodyHorizontal;
    } else {
      return bodyVertical;
    }
  }
}

std::vector<sf::Vector2f>& Snake::getSnakeBody() {
  return bodyArray;
}