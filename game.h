#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>

class Game {
 private:
  /* data */
 public:
  Game();

  static void init();
  static void start();
  void pause();
  void resume();
  // ~Game();
};

#endif