#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include <sstream>

#include "assets.h"
#include "food.h"
#include "snake.h"

class Game {
 private:
  bool isRunning;
  int score;
  int highScore;

  sf::Sprite scoreSprite;
  sf::Sprite highScoreSprite;
  sf::Texture highScoreSpriteTexture;

  sf::Font gameFont;
  sf::Text scoreText;
  sf::Text highScoreText;

  Snake snake;
  Food food;

  Assets assets;

 public:
  Game();

  static void init();
  void start();
  void pause();
  void resume();
  void updateScore();

  void drawBoard(sf::RenderWindow*);
  void drawSnake(sf::RenderWindow*);
  // ~Game();
};

#endif