#include "game.h"
#include "constants.h"

Game::Game() : isRunning{false}, score{0}, highScore{0} {
  food.move(true);
  scoreSprite.setTexture(*food.getBody().getTexture());
  scoreSprite.setPosition(20, 10);

  if (!highScoreSpriteTexture.loadFromFile("assets/images/trophy.png")) {
    return;
  } else {
    highScoreSpriteTexture.setSmooth(true);
    highScoreSprite.scale(0.28, 0.28);
    highScoreSprite.setTexture(highScoreSpriteTexture);
    highScoreSprite.setPosition(150, 12);
  }

  gameFont.loadFromFile("assets/fonts/qualy_bold.ttf");

  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setFont(gameFont);
  scoreText.setPosition(85, 12);
  highScoreText.setCharacterSize(30);
  highScoreText.setFillColor(sf::Color::White);
  highScoreText.setFont(gameFont);
  highScoreText.setPosition(215, 12);
  updateScore();
}

void Game::updateScore() {
  std::stringstream ss;
  std::string strScore, strHighScore;

  ss << score;
  ss >> strScore;
  scoreText.setString(strScore);

  ss.clear();
  ss << highScore;
  ss >> strHighScore;
  highScoreText.setString(strHighScore);
}

void Game::init() {}

void Game::drawBoard(sf::RenderWindow* window) {
  for (int y{0}; y < (screenHeight + 120) / blockHeight; y++) {
    for (int x{0}; x < (screenWidth + 60) / blockWidth; x++) {
      if (y < 2) {
        assets.borderDark.setPosition(x * blockWidth, y * blockHeight);
        window->draw(assets.borderDark);
      } else if (x == 0 || y == 2 ||
                 x == ((screenWidth + 60) / blockWidth) - 1 ||
                 y == (((screenHeight + 120) / blockHeight) - 1)) {
        assets.borderLight.setPosition(x * blockWidth, y * blockHeight);
        window->draw(assets.borderLight);
      } else if ((x + y) & 1) {
        assets.grassLight.setPosition(x * blockWidth, y * blockHeight);
        window->draw(assets.grassLight);
      } else {
        assets.grassDark.setPosition(x * blockWidth, y * blockHeight);
        window->draw(assets.grassDark);
      }
    }
  }
}

void Game::drawSnake(sf::RenderWindow* window) {
  auto snakeBody = snake.getSnakeBody();
  for (size_t i{0}; i < snakeBody.size(); i++) {
    snake.getBodySprite(i).setPosition(snakeBody[i]);
    window->draw(snake.getBodySprite(i));
  }
}

void Game::start() {
  sf::RenderWindow window{sf::VideoMode(screenWidth + 60, screenHeight + 120),
                          "Snake"};
  window.setFramerateLimit(frameRate);

  sf::Vector2f movement{5, 0};
  int frameCount{0};

  std::srand(time(nullptr));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if (!isRunning)
          isRunning = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          movement.x = stepCount;
          movement.y = 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          movement.x = -stepCount;
          movement.y = 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          movement.x = 0;
          movement.y = -stepCount;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          movement.x = 0;
          movement.y = stepCount;
        }
      }
    }

    frameCount++;
    if (!(frameCount % (blockWidth / stepCount))) {
      snake.setMovement(movement);
    }

    snake.move();
    if (snake.checkEat(food.getPosition())) {
      food.move(true);
      score++;
      updateScore();
    }

    drawBoard(&window);
    drawSnake(&window);
    window.draw(scoreSprite);
    window.draw(highScoreSprite);
    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(food.getBody());
    window.display();
  }
}

void Game::pause() {}

void Game::resume() {}