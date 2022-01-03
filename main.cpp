#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "snake.h"
#include "food.h"
#include "constants.h"

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

    Snake snake {};
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