#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int blockWidth = 30;
const int blockHeight = 30;

const int screenWidth = 540;
const int screenHeight = 480;

const int frameRate = 60;
const int stepCount = 5;

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
    Snake()
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

    void eat()
    {
        auto bodyLast = bodyArray[bodyArray.size() - 1];
        auto movementLast = movements[movements.size() - 1];
        bodyLast += sf::Vector2f((movementLast.x / 5) * blockWidth * -1,
                                 (movementLast.y / 5) * blockHeight * -1);
        bodyArray.push_back(bodyLast);
        movements.push_back(movementLast);
        bodyArrayTemp = bodyArray;
    }

    void move()
    {
        for (size_t i{0}; i < bodyArray.size(); i++)
        {
            bodyArray[i] += movements[i];
        }
    }

    void setMovement(sf::Vector2f newMovement)
    {
        if (newMovement != movements[0])
            moveSound.play();
        movements.insert(movements.begin(), newMovement);
        movements.pop_back();
    }

    bool checkEat(sf::Vector2f foodPos)
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

    sf::Vector2f &getHead()
    {
        return bodyArray[0];
    }

    std::vector<sf::Vector2f> &getSnakeBody()
    {
        return bodyArray;
    }
};

class Food
{
private:
    sf::Sprite body;
    sf::Texture bodyTexture{};
    sf::Vector2f position{120, 120};

public:
    Food()
    {
        if (!bodyTexture.loadFromFile("./assets/images/apple.png"))
        {
            std::cout << sf::err;
        }
        else
        {
            bodyTexture.setSmooth(true);
            body.setTexture(bodyTexture);
            body.scale(((double)blockWidth / bodyTexture.getSize().x) * 1.5,
                       ((double)blockHeight / bodyTexture.getSize().y) * 1.5);
        }
    };

    void move(bool checkMove)
    {
        if (!checkMove)
            return;

        position.x = (std::rand() % screenWidth / blockWidth) * blockWidth;
        position.y = (std::rand() % screenHeight / blockHeight) * blockHeight;
        body.setPosition(position.x - 8, position.y - 8);
    }

    sf::Sprite &getBody()
    {
        return body;
    }

    sf::Vector2f &getPosition()
    {
        return position;
    }
};

int main()
{
    sf::RenderWindow window{sf::VideoMode(screenWidth, screenHeight), "Shapes"};
    window.setFramerateLimit(frameRate);

    sf::RectangleShape body{sf::Vector2f{blockWidth, blockHeight}};
    body.setFillColor(sf::Color::White);

    sf::RectangleShape grassLight{sf::Vector2f{blockWidth, blockHeight}};
    grassLight.setFillColor(sf::Color(0xAAD751FF));

    sf::RectangleShape grassDark{sf::Vector2f{blockWidth, blockHeight}};
    grassDark.setFillColor(sf::Color(0xA2D149FF));

    sf::Vector2f movement{0, 0};
    int frameCount{0};

    std::srand(time(nullptr));

    Snake snake;
    Food food;
    food.move(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    movement.x = stepCount;
                    movement.y = 0;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    movement.x = -stepCount;
                    movement.y = 0;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    movement.x = 0;
                    movement.y = -stepCount;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    movement.x = 0;
                    movement.y = stepCount;
                }
            }
        }

        frameCount++;
        if (!(frameCount % (blockWidth / stepCount)))
        {
            snake.setMovement(movement);
        }

        snake.move();
        food.move(snake.checkEat(food.getPosition()));

        for (int y{0}; y < screenHeight / blockHeight; y++)
        {
            for (int x{0}; x < screenWidth / blockWidth; x++)
            {
                if ((x + y) & 1)
                {
                    grassLight.setPosition(x * blockWidth, y * blockHeight);
                    window.draw(grassLight);
                }
                else
                {
                    grassDark.setPosition(x * blockWidth, y * blockHeight);
                    window.draw(grassDark);
                }
            }
        }

        for (const sf::Vector2f &part : snake.getSnakeBody())
        {
            body.setPosition(part);
            window.draw(body);
        }

        window.draw(food.getBody());
        window.display();
    }

    return 0;
}