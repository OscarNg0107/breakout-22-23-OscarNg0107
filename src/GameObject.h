#include<SFML/Graphics.hpp>
#include "Vector2.h"
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

class GameObject
{
 public:
  bool visibilty = true;
  bool moving_left = false;
  bool moving_right = false;
  bool isVisible() ;
  Vector2 direction= Vector2(0,0);

  sf::Sprite object;

  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename, sf::RenderWindow& game_window);
  sf::Sprite* getSprite();

 private:
  sf::Sprite* sprite = nullptr;

};



#endif // BREAKOUT_GAMEOBJECT_H
