
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include <sstream>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  int update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  sf::Time getElasped();
  void RestartClock();

  enum Gamestate {MainMenu, InGame, GameOver , GameWon};

 private:
  sf::RenderWindow& window;

  Gamestate gamestate = MainMenu;

  sf::Texture background_texture;
  sf::Text title_text;
  sf::Text start_text;



  bool start = false;
  sf::Text ingame_start_text;

  sf::Clock clock1;
  sf::Time elapsed;


  sf::Text life_counter_text;
  int number_of_lives = 3;
  std::ostringstream lives_left;

  int score = 0;
  sf::Text game_score;
  std::ostringstream score_number;


  GameObject ball;
  sf::Sprite ball_sprite;
  sf::Texture ball_texture;
  sf::Font font;
  sf::FloatRect nextPos;

  void Reset();
  void GameReset();

  bool CollisionCheck(sf::Sprite sprite1, sf::Sprite sprite2, float dt);
  bool side_collision = false;
  bool top_coliision = false;

  GameObject  paddle;
  sf::Sprite paddle_sprite;
  sf::Texture paddle_texture;

  GameObject wall [24];
  sf::Sprite wall_sprite[24];
  sf::Texture wall_texture;
  int wall_y = 12;
  int wall_x= 2;

  GameObject blocks[84];
  sf::Sprite block_sprite[84];
  sf::Texture block_texture;
  int grid_size_x = 14;
  int grid_size_y = 6;
  int hit_counter = 0;

  int number_of_gems = 20;
  GameObject gems[20];
  sf::Texture gem_texture;
  sf::Sprite gem_sprite[20];


  sf::Text congrates_text;
  sf::Text final_score;
  sf::Text replay_text;
  bool win_selected_text = true;

  sf::Text game_over_text;
  sf::Text restart_text;
  sf::Text quit_text;
  bool over_selected_text = true;
};

#endif // BREAKOUT_GAME_H
