#include "world.hpp"
#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

<<<<<<< HEAD
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
=======
  moi.start();
  sf::RenderWindow Window(sf::VideoMode(100, 100), "Q-learning");
>>>>>>> 85a4a99526d6282d474778dbf4201871de1dbf24

    return 0;
}
