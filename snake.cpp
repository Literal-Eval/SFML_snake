#include "snake.h"

Snake::Snake()
{
    if (!moveSoundBuffer.loadFromFile("assets/music/move.wav"))
    {
        std::cout << sf::err;
    }
    else
    {
        moveSound.setBuffer(moveSoundBuffer);
    }
};

void Snake::eat()
{
    auto bodyLast = bodyArray[bodyArray.size() - 1];
    auto movementLast = movements[movements.size() - 1];
    bodyLast += sf::Vector2f((movementLast.x / 5) * blockWidth * -1,
                             (movementLast.y / 5) * blockHeight * -1);
    bodyArray.push_back(bodyLast);
    movements.push_back(movementLast);
    bodyArrayTemp = bodyArray;
}

void Snake::move()
{
    for (size_t i{0}; i < bodyArray.size(); i++)
    {
        bodyArray[i] += movements[i];
    }
}

void Snake::setMovement(sf::Vector2f newMovement)
{
    if (newMovement != movements[0])
        moveSound.play();
    movements.insert(movements.begin(), newMovement);
    movements.pop_back();
}

bool Snake::checkEat(sf::Vector2f foodPos)
{
    auto headPos{bodyArray[0]};
    auto tempPos{headPos + movement};

    if ((tempPos.x == foodPos.x) &&
            ((tempPos.y > foodPos.y && tempPos.y < foodPos.y + blockHeight) ||
             (tempPos.y + blockHeight > foodPos.y && tempPos.y < foodPos.y)) ||
        (tempPos.y == foodPos.y) &&
            ((tempPos.x > foodPos.x && tempPos.x < foodPos.x + blockWidth) ||
             (tempPos.x + blockWidth > foodPos.x && tempPos.x < foodPos.x)))
    {
        eat();
        return true;
    }
    return false;
}

sf::Vector2f &Snake::getHead()
{
    return bodyArray[0];
}

std::vector<sf::Vector2f> &Snake::getSnakeBody()
{
    return bodyArray;
}