#include "flappy.hpp"

FlappyBird::FlappyBird()
{
       window = std::make_shared<sf::RenderWindow>(
           sf::VideoMode(1000, 600),
           "Flappy Bird (remix)",
           sf::Style::Titlebar | sf::Style::Close);

       window->setPosition(sf::Vector2i(0, 0));
       window->setFramerateLimit(60);

       gravity = frame = {0.f};
       space = {160.f};
       count = {0};
       bg.loadFromFile("./resources/background.png");
       flappy.loadFromFile("./resources/flappy.png");
       pipe.loadFromFile("./resources/pipe.png");

       background = std::make_shared<sf::Sprite>();
       bird = std::make_shared<sf::Sprite>();
       pipeBottom = std::make_shared<sf::Sprite>();
       pipeTop = std::make_shared<sf::Sprite>();

       background->setTexture(bg);
       bird->setTexture(flappy);
       pipeBottom->setTexture(pipe);
       pipeTop->setTexture(pipe);

       bird->setPosition(
           500.f - flappy.getSize().x / 2.f,
           300.f - flappy.getSize().y / 2.f);

       bird->setScale(2.f, 2.f);
       bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

       pipeBottom->setScale(1.5f, 1.5f);
       pipeTop->setScale(1.5f, 1.5f);

       gameover = {false};
       score = {0};

       font.loadFromFile("./font/flappybird.ttf");

       txt_gameover.setFont(font);
       txt_gameover.setString("Aperte espaco para continuar");
       txt_gameover.setPosition(150, 200);
       txt_gameover.setCharacterSize(50);
       txt_gameover.setOutlineThickness(3);

       txt_score.setFont(font);
       txt_score.setString(std::to_string(score));
       txt_score.setPosition(10.f, 10.f);
       txt_score.setCharacterSize(50);
       txt_score.setOutlineThickness(3);
}

void FlappyBird::events()
{
       auto e = std::make_shared<sf::Event>();
       while (window->pollEvent(*e))
       {
              if (e->type == sf::Event::Closed)
              {

                     window->close();
              }
       }
}

void FlappyBird::draw()
{
       window->clear(sf::Color::Black);
       window->draw(*background);

       for (auto &p : pipes)
       {
              window->draw(p);
       }

       window->draw(*bird);

       if (gameover)
       {
              window->draw(txt_gameover);
       }

       window->draw(txt_score);
       window->display();
}

void FlappyBird::run()
{
       while (window->isOpen())
       {
              events();
              draw();
              game();
              ++count;

              if (count == 300)
              {
                     count = 0;
              }
       }
}

void FlappyBird::movePipes()
{

       if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
       {
              gravity = -8.f;
              bird->setRotation(-frame - 15.f);
       }
       else
       {
              bird->setRotation(frame);
       }

       if (count % 150 == 0)
       {
              int pos = std::rand() % 275 + 175;

              pipeBottom->setPosition(1000, pos + space);
              pipeTop->setPosition(1000, pos);

              pipes.push_back(*pipeBottom);
              pipes.push_back(*pipeTop);
       }

       for (std::size_t i{}; i < pipes.size(); ++i)
       {

              if (pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds()))
              {
                     gameover = true;
              }

              if (pipes[i].getPosition().x < -100)
              {

                     pipes.erase(pipes.begin() + i);
              }

              if (pipes[i].getPosition().x == 448)
              {
                     int s = ++score;

                     txt_score.setString(std::to_string(s / 2));
              }

              pipes[i].move(-4.f, 0);
       }
}

void FlappyBird::game()
{
       if (!gameover)
       {
              moveBird();
              setAnimeBird();
              movePipes();
       }

       if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
       {

              bird->setPosition(
                  500.f - flappy.getSize().x / 2.f,
                  300.f - flappy.getSize().y / 2.f);

              gameover = false;

              std::cout << "Game Over" << std::endl;
       }
}

void FlappyBird::setAnimeBird()
{
       frame += 0.15f;

       if (frame > 3)
       {

              frame -= 3;
       }

       bird->setTextureRect(sf::IntRect(34 * (int)frame, 0, 34, 24));
}

void FlappyBird::moveBird()
{

       bird->move(0, gravity);
       gravity += 0.5f;
}