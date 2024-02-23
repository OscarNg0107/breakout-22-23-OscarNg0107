
#include "Game.h"
#include <iostream>


Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  //Game main menu setting
  if(!font.loadFromFile("Data/Fonts/open-sans/OpenSans-Bold.ttf"))
  {
    std::cout << "Font loading error";
  }

  title_text.setString("Breakout");
  title_text.setFont(font);
  title_text.setCharacterSize(150);
  title_text.setFillColor(sf::Color(255,255,255,255));
  title_text.setPosition(window.getSize().x/2 - title_text.getGlobalBounds().width/2,
                         window.getSize().y/2 - title_text.getGlobalBounds().height *2);

  start_text.setString("[Press Enter to start]");
  start_text.setFont(font);
  start_text.setCharacterSize(50);
  start_text.setFillColor(sf::Color(255,255,255,150));
  start_text.setPosition(window.getSize().x/2 - start_text.getGlobalBounds().width /2,
                         window.getSize().y - start_text.getGlobalBounds().height *4);


  //Gameplay screen setting

  ingame_start_text.setString("Press Space to start");
  ingame_start_text.setFont(font);
  ingame_start_text.setCharacterSize(40);
  ingame_start_text.setFillColor(sf::Color(255,255,255,125));
  ingame_start_text.setPosition(window.getSize().x/2 - ingame_start_text.getGlobalBounds().width/2,
                                window.getSize().y - 200);


  // life counter
  lives_left << number_of_lives;
  life_counter_text.setString("Life: "  + lives_left.str() );
  life_counter_text.setFont(font);
  life_counter_text.setCharacterSize(50);
  life_counter_text.setFillColor(sf::Color(255,255,255,255));
  life_counter_text.setPosition(window.getSize().x*3 /4 + 20, 50);


  score_number << score;
  game_score.setString("Score: \n" + score_number.str());
  game_score.setFont(font);
  game_score.setCharacterSize(50);
  game_score.setFillColor(sf::Color(255,255,255,255));
  game_score.setPosition(10, 50);


  //wall
  for(int i = 0; i < wall_x ; i++)
  {
    for(int j =0 ; j <wall_y; j++ )
    {
      if(!wall[i* wall_y +j].initialiseSprite(wall_texture,"Data/Images/element_grey_rectangle_glossy.png", window))
      {
        std::cout << "wall texture loading error";
      }
      wall_sprite[i* wall_y +j] = *wall[i* wall_y +j].getSprite();
      wall_sprite[i* wall_y +j].setScale(1.0f, 1.0f);
      wall_sprite[i* wall_y +j].setPosition((window.getSize().x /4 - wall_sprite[i* wall_y +j].getGlobalBounds().height) + 585* i,
                                 0 + wall_sprite[i* wall_y +j].getGlobalBounds().height * j );
    }

  }

  //paddle
  if (!paddle.initialiseSprite(paddle_texture, "Data/Images/paddleRed.png", window))
  {
    std::cout << "paddle texture loading error";
  }

  paddle_sprite = *paddle.getSprite();


  //ball
  if(!ball.initialiseSprite(ball_texture, "Data/Images/ballGrey.png",window))
  {
    std::cout <<"ball texture loading error";
  }

  ball_sprite= *ball.getSprite();
  ball_sprite.setPosition(window.getSize().x/4 +ball_sprite.getGlobalBounds().width *2,
                          window.getSize().y/2- ball_sprite.getGlobalBounds().height/2);

  //blocks
  for(int i = 0; i < grid_size_x; i++)
  {
    for(int j = 0; j < grid_size_y; j++)
    {
      if (!blocks[i * grid_size_y +j].initialiseSprite(
            block_texture, "Data/Images/element_blue_square.png", window))
      {
        std::cout << "block texture loading error";
      }
      block_sprite[i * grid_size_y +j] = *blocks[i * grid_size_y +j].getSprite();
      block_sprite[i * grid_size_y +j].setScale(1.0f, 1.0f);
      block_sprite[i * grid_size_y +j].setPosition(
        window.getSize().x / 4 + 35 * i, window.getSize().y - 650 + 40* j);
      blocks[i * grid_size_y +j].isVisible();
    }
  }


  //gems
  for( int i = 0; i < number_of_gems ; i++)
  {
    if(!gems[i].initialiseSprite(gem_texture, "Data/Images/element_red_diamond_glossy.png", window))
    {
      std::cout << "gem texture loading error";
    }
    gem_sprite[i] = *gems[i].getSprite();
    gem_sprite[i].setPosition( int(window.getSize().x /4 - wall_sprite->getGlobalBounds().width )+
                                (std::rand()% int( (window.getSize().x/4 -wall_sprite->getGlobalBounds().width *2 + 585 - gem_sprite[i].getGlobalBounds().width) -
                                                   (window.getSize().x /4 -wall_sprite->getGlobalBounds().width)) +1 ),

                              0 - gem_sprite[i].getGlobalBounds().height);
    gems[i].isVisible();
    gems[i].direction = Vector2(0, 4.0f);
    gems[i].direction.normalise();
  }


  congrates_text.setString("Congratulations!");
  congrates_text.setFont(font);
  congrates_text.setCharacterSize(100);
  congrates_text.setFillColor(sf::Color(255,255,255,255));
  congrates_text.setPosition(window.getSize().x/2 - congrates_text.getGlobalBounds().width /2,
                             200);

  final_score.setString("Your Score is: " + score_number.str());
  final_score.setFont(font);
  final_score.setCharacterSize(75);
  final_score.setFillColor(sf::Color(255,255,255,255));
  final_score.setPosition(window.getSize().x /2 - final_score.getGlobalBounds().width/2,
                          window.getSize().y/2 - final_score.getGlobalBounds().height/2);

  replay_text.setString("Replay");
  replay_text.setFont(font);
  replay_text.setCharacterSize(50);
  replay_text.setFillColor(sf::Color(255,255,255,125));
  replay_text.setPosition(window.getSize().x /4 - replay_text.getGlobalBounds().width/2,
                          window.getSize().y -200 );


  //gameover screen text
  game_over_text.setString("GAME OVER");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(100);
  game_over_text.setFillColor(sf::Color(255,255,255,255));
  game_over_text.setPosition(window.getSize().x/2 - game_over_text.getGlobalBounds().width/2,
                             100);

  restart_text.setString("Restart");
  restart_text.setFont(font);
  restart_text.setCharacterSize(50);
  restart_text.setFillColor(sf::Color(255,255,255,125));
  restart_text.setPosition(window.getSize().x/4 - restart_text.getGlobalBounds().width/2,
                           window.getSize().y - 200);

  quit_text.setString("Quit");
  quit_text.setFont(font);
  quit_text.setCharacterSize(50);
  quit_text.setFillColor(sf::Color(255,255,255,125));
  quit_text.setPosition( window.getSize().x *3 /4 - quit_text.getGlobalBounds().width/2,
                        window.getSize().y - 200);

  return true;
}

int Game::update(float dt)
{
  if(gamestate == MainMenu)
  {
    RestartClock();
  }
  if (gamestate == InGame)
  {
    for (int i = 0; i< grid_size_x * grid_size_y ; i++)
    {
      if(blocks[i].visibilty)
      {
        if (CollisionCheck(ball_sprite, block_sprite[i], dt))
        {
          if (!top_coliision)
          {
            ball.direction.y *= -1;
          }
          if (!side_collision)
          {
            ball.direction.x *= -1;
          }
          blocks[i].visibilty = false;
          hit_counter += 1;
          score+= 1;
          score_number.str("");
          score_number << score;
          game_score.setString("Score: \n" + score_number.str());
          final_score.setString("Your Score is: " + score_number.str());
        }
      }
    }



    //paddle movement
    if (paddle.moving_left && paddle_sprite.getPosition().x > window.getSize().x /4 - wall_sprite->getGlobalBounds().width)
    {
      paddle_sprite.move(-1 * paddle.direction.operator*(400).x * dt, 0);
    }
    if (paddle.moving_right && paddle_sprite.getPosition().x + paddle_sprite.getGlobalBounds().width <
      window.getSize().x/4 - wall_sprite->getGlobalBounds().width *2 + 585)
    {
      paddle_sprite.move(paddle.direction.operator*(400).x * dt, 0);
    }

    //ball movement
    ball_sprite.move(ball.direction.operator*(200).x *dt,ball.direction.operator*(300).y *dt);



    //ball wall bounce

    if(ball_sprite.getPosition().y < 0)
    {
      ball.direction.y *= -1;
    }
    if(ball_sprite.getPosition().x < window.getSize().x /4 - wall_sprite->getGlobalBounds().height /2 ||
        ball_sprite.getPosition().x+ ball_sprite.getGlobalBounds().height > window.getSize().x/4 - wall_sprite->getGlobalBounds().height  + 585)
    {
      ball.direction.x *= -1;
    }
    if(CollisionCheck(ball_sprite, paddle_sprite, dt) == true)
    {
      ball.direction.y *= -1;
    }

    //ball reach the buttom
    if(ball_sprite.getPosition().y > window.getSize().y)
    {
      number_of_lives -= 1;
      lives_left.str("");
      lives_left << number_of_lives;
      life_counter_text.setString("Life: " + lives_left.str());
      Reset();
    }

    //gems fall
    if(start)
    {
      for(int i =0 ; i < number_of_gems ; i++)
      {
        if(int (getElasped().asSeconds() )>= (5 + i*8))
        {
          gems[i].direction = Vector2(0, 4.0f);
          gems[i].direction.normalise();
          if(gems[i].visibilty)
          {
            gem_sprite[i].move(0,gems[i].direction.operator*(300).y *dt);
          }

          if(gem_sprite[i].getPosition().y >= window.getSize().y)
          {
            gems[i].visibilty = false;
          }
        }
      }
    }

    for(int i =0 ; i < number_of_gems ; i++)
    {
      if (gems[i].visibilty)
      {
        if (CollisionCheck(gem_sprite[i], paddle_sprite, dt))
        {
          gems[i].visibilty = false;
          score += 3;
          score_number.str("");
          score_number << score;
          game_score.setString("Score: \n" + score_number.str());
          final_score.setString("Your Score is: " + score_number.str());
        }
      }
    }


    if (hit_counter == grid_size_y*grid_size_x)
    {
      gamestate = GameWon;
    }


    //PLayer lost all the lives
    if (number_of_lives == 0 )
    {
      gamestate = GameOver;
    }
  }
  if(gamestate == GameOver)
  {
    if (over_selected_text)
    {
      restart_text.setFillColor(sf::Color(255,255,255,255));
      quit_text.setFillColor(sf::Color(255,255,255,125));
    }
    else
    {
      restart_text.setFillColor(sf::Color(255,255,255,125));
      quit_text.setFillColor(sf::Color(255,255,255,255));
    }
  }


  if(gamestate == GameWon)
  {
    if (win_selected_text)
    {
      replay_text.setFillColor(sf::Color(255,255,255,255));
      quit_text.setFillColor(sf::Color(255,255,255,125));
    }
    else
    {
      replay_text.setFillColor(sf::Color(255,255,255,125));
      quit_text.setFillColor(sf::Color(255,255,255,255));
    }
  }
}

void Game::render()
{
  if(gamestate == MainMenu)
  {
    window.draw(title_text);
    window.draw(start_text);
  }

  if(gamestate == InGame)
  {
    if(!start)
    {
      window.draw(ingame_start_text);
    }
    window.draw(life_counter_text);
    window.draw(game_score);
    window.draw(paddle_sprite);

    for(int i =0 ; i <wall_x * wall_y ; i++)
    {
        window.draw(wall_sprite[i]);

    }


    for (int i = 0; i< grid_size_x * grid_size_y ; i++)
    {
      if(blocks[i].visibilty)
      {
        window.draw(block_sprite[i]);
      }
    }


    for(int i = 0 ; i < number_of_gems ; i++)
    {
      if(gems[i].visibilty)
      {
        window.draw(gem_sprite[i]);
      }
    }
    window.draw(ball_sprite);
  }

  if (gamestate == GameOver)
  {
    window.draw(game_over_text);
    window.draw(final_score);
    window.draw(restart_text);
    window.draw(quit_text);
  }

  if(gamestate == GameWon)
  {
    window.draw(congrates_text);
    window.draw(final_score);
    window.draw(replay_text);
    window.draw(quit_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  if( gamestate == MainMenu)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      gamestate = InGame;
    }
  }

  if (gamestate == InGame)
  {
    if(!start)
    {
      if (event.key.code == sf::Keyboard::Space)
      {
        RestartClock();
        start = true;
        ball.direction = Vector2(3.0f, 4.0f);
        ball.direction.normalise();
        paddle.direction = Vector2(6.0f, 0.0);
        paddle.direction.normalise();
      }
    }
    else
    {
      if(event.key.code == sf::Keyboard::A)
      {
        paddle.moving_left = true;
      }
      if(event.key.code == sf::Keyboard::D)
      {
        paddle.moving_right = true;
      }
    }

  }

  if (gamestate == GameOver)
  {
    if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))
    {
      over_selected_text = !over_selected_text;
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if(over_selected_text)
      {
        GameReset();
        gamestate = InGame;

      }
      else
      {
        window.close();

      }
    }
  }

  if(gamestate == GameWon)
  {
    if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))
    {
      win_selected_text = !win_selected_text;
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if(win_selected_text)
      {
        GameReset();
        gamestate = InGame;
      }
      else
      {
        window.close();
      }
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if(gamestate ==InGame)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      paddle.moving_left = false;
    }
    if(event.key.code == sf::Keyboard::D)
    {
      paddle.moving_right = false;
    }
  }
}


bool Game::CollisionCheck(sf::Sprite sprite1, sf::Sprite sprite2, float dt)
{
  sf::FloatRect rect1 = sprite1.getGlobalBounds();
  sf::FloatRect rect2 = sprite2.getGlobalBounds();

  nextPos = rect1;
  nextPos.left += ball.direction.operator*(200).x *dt;
  nextPos.top += ball.direction.operator*(300).y*dt;

  if (rect2.intersects(nextPos))
  {
    //block bottom collision
    if(
      rect1.top > rect2.top &&
        rect1.top +rect1.height> rect2.top +rect2.height &&
        rect1.left < rect2.left + rect2.width &&
        rect1.left + rect1.width > rect2.left &&
        !side_collision )
    {
      //ball.direction.y = 0;
      sprite1.setPosition(rect1.left, rect2.top + rect2.height);
      if (!top_coliision)
      {
        top_coliision = true;
      }
      else
      {
        top_coliision = false;
      }
    }
    //block Top collision
    else if(
      rect1.top < rect2.top &&
             rect1.top +rect1.height< rect2.top +rect2.height &&
             rect1.left < rect2.left + rect2.width &&
             rect1.left + rect1.width > rect2.left &&
             !side_collision)

    {
      //ball.direction.y = 0;
      sprite1.setPosition(rect1.left, rect2.top - rect1.height );
      if (!top_coliision)
      {
        top_coliision = true;
      }
      else
      {
        top_coliision = false;
      }
    }

    //block right collision
    if(
        rect1.left > rect2.left &&
        rect1.left + rect1.width > rect2.left + rect2.width&&
        rect1.top < rect2.top + rect2.height &&
        rect1.top + rect1.height > rect2.top &&
        !top_coliision)
    {
      //ball.direction.x = 0;
      sprite1.setPosition(rect2.left+ rect2.width, rect1.top);
      if(!side_collision)
      {
        side_collision = true;
      }
      else
      {
        side_collision = false;
      }
    }

    //block left collision
    else if (
              rect1.left < rect2.left &&
             rect1.left + rect1.width < rect2.left + rect2.width&&
             rect1.top < rect2.top + rect2.height &&
             rect1.top + rect1.height > rect2.top &&
             !top_coliision)
    {
      //ball.direction.x = 0;
      sprite1.setPosition(rect2.left - rect1.width  , rect1.top);
      if(!side_collision)
      {
        side_collision = true;
      }
      else
      {
        side_collision = false;
      }
    }
    return true;
  }
  return false;
}


void Game::Reset()
{
  start = false;
  RestartClock();
  ball_sprite.setPosition(window.getSize().x/4 +ball_sprite.getGlobalBounds().width *2,
                          window.getSize().y/2- ball_sprite.getGlobalBounds().height/2);
  ball.direction = Vector2(0,0);
  ball.direction.normalise();
  paddle_sprite.setPosition(
    window.getSize().x / 2 - paddle_sprite.getGlobalBounds().width / 2,
    window.getSize().y - paddle_sprite.getGlobalBounds().height * 4);
  for (int i = 0; i < number_of_gems ; i++ )
  {
    gem_sprite[i].setPosition( int(window.getSize().x /4 - wall_sprite->getGlobalBounds().width )+
                                (std::rand()% int( (window.getSize().x/4 -wall_sprite->getGlobalBounds().width *2 + 585 - gem_sprite[i].getGlobalBounds().width) -
                                                   (window.getSize().x /4 -wall_sprite->getGlobalBounds().width)) +1 ),
                              0 - gem_sprite[i].getGlobalBounds().height);
    gems[i].visibilty = true;
  }
}

void Game::GameReset()
{
  Reset();
  number_of_lives = 3;
  lives_left.str("");
  lives_left << number_of_lives;
  life_counter_text.setString("Life: "+ lives_left.str());


  score = 0;
  score_number.str("");
  score_number<< score;
  game_score.setString("Score: "+ score_number.str());

  for(int i; i <grid_size_y*grid_size_x ; i++)
  {
    blocks[i].visibilty = true;
  }
}
sf::Time Game::getElasped()
{
  elapsed = clock1.getElapsedTime();
  return elapsed;
}
void Game::RestartClock()
{
  clock1.restart();
}


