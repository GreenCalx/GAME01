#include "Engine.h"

#define FRAMES_PER_SEC 60

int main()
{
	/** Initialization **/
	sf::RenderWindow window(sf::VideoMode(800, 600), "The Mauve Game");
	Engine& engine = Engine();

	// Game clock init
	sf::Clock clock;
	sf::Time clock_rate = sf::milliseconds(1.0f / FRAMES_PER_SEC);
	sf::Time elapsed;
	window.setFramerateLimit(FRAMES_PER_SEC);

	while (window.isOpen())
	{
		sf::Event event;
		elapsed = clock.getElapsedTime();

		if (elapsed >= clock_rate) {

			if (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == event.KeyPressed) {
					engine.updateInputs();
				}
			}

			engine.update();
		}

		/*
		while (window.pollEvent(event))
		{
			if ( event.type == sf::Event::Closed ) {
				window.close();
			}
			if ( event.type == event.KeyPressed ) {
				engine.updateInputs();
			}
		}
		*/
		window.clear();
		engine.drawScene(window);
		window.display();
		clock.restart();
	}

	return 0;
}