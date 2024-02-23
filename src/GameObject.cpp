#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  sprite = new sf::Sprite;
}
bool GameObject::initialiseSprite(
  sf::Texture& texture, std::string filename, sf::RenderWindow& game_window)
{
  if (!texture.loadFromFile(filename))
  {
    return false;
  }
  object.setTexture(texture);
  object.setPosition(
    game_window.getSize().x / 2 - object.getGlobalBounds().width / 2,
    game_window.getSize().y - object.getGlobalBounds().height * 2);

  object.setScale(0.5f, 0.5f);
  direction.normalise();
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  sprite  = &object;
  *sprite = object;
  return sprite;
}

GameObject::~GameObject()
{
  if(sprite != nullptr)
  {
    delete sprite;
    sprite = nullptr;
  }
}

bool GameObject::isVisible()
{
  visibilty = true;
}
