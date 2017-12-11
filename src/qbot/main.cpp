#include "brains.hpp"
#include "draw.hpp"
#include "world.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

const float SCALE = 10.f;
const int windowWidth = 1400;
const int windowHeight = 600;

int main() {
    // Create window for the program
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test");
    window.setFramerateLimit(60);
    // Views allow us to move the camera with the wurm
    window.setView(view1);

    // Stage the world, brains and drawing function
    World* worldy = new World();
    b2World world = *(worldy->GetWorld());
    Brains* b = new Brains(24, &world);

    int startPos = b->GetWurm()->GetWurmPosition()->x;

    Draw draw;
    int iterations = 0;

    sf::Font font;
    if(font.loadFromFile("./../Montserrat-Regular.ttf")) {
      std::cout << "Font loaded!" << std::endl;
    }

    // Main loop
    while (window.isOpen()) {
        auto xyy = b->GetWurm()->GetWurmPosition();
        view1.setCenter(xyy->x*SCALE, xyy->y*SCALE);
        window.setView(view1);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);
        b->Think();
        iterations++;

        // Draw here
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(12);
        text.setColor(sf::Color::Black);
        // Gather info
        auto infotext = "Iterations: " + std::to_string(iterations);
        infotext += "\nPosition X: " + std::to_string(b->GetWurm()->GetWurmPosition()->x);
        infotext += "\nVelocity: N/A";

        text.setString(infotext);
        text.setPosition(view1.getCenter()-sf::Vector2f(675.f,275.f));

        window.clear(sf::Color::White);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        window.draw(text);
        window.display();
    }

    std::cout << "Total distance travelled: " <<
              b->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
