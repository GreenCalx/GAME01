#include "Engine.h"

const int FRAMES_PER_SEC			= 60;
const int INPUT_CHECK_PER_SECOND	= 60;
const int GRAPHICAL_UPDATE_PER_SEC	= 4;

int main()
{
	/** Initialization **/
	Engine& engine = Engine();
	sf::RenderWindow window(sf::VideoMode(__SCREEN_WIDTH, __SCREEN_HEIGHT), "The Mauve Game");
	window.setFramerateLimit(FRAMES_PER_SEC);

	// Game clocks init
	sf::Clock clock, graphicalUpdateClock;;
	sf::Time inputUpdate_clock_rate = sf::seconds(1.0f / INPUT_CHECK_PER_SECOND);
	sf::Time graphicalUpdate_clock_rate = sf::seconds(1.0f / GRAPHICAL_UPDATE_PER_SEC);
	sf::Time elapsed, graphicalUpdateElapsed;
	
	while (window.isOpen())
	{
		sf::Event event;
		elapsed					= clock.getElapsedTime();
		graphicalUpdateElapsed	= graphicalUpdateClock.getElapsedTime();

		window.setView(*engine.getCamera()->getView());

		if (graphicalUpdateElapsed >= graphicalUpdate_clock_rate) {
			engine.updateGraphics();
			graphicalUpdateClock.restart();
		}

		if (elapsed >= inputUpdate_clock_rate) {

			if (window.pollEvent(event)) {

				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == event.KeyPressed || event.type == sf::Event::KeyReleased) {
					engine.updateInputs();
				}

			}

				
			engine.update();
			window.setView(*engine.getCamera()->getView());

			window.clear();
			engine.drawScene(window);
			window.display();

			clock.restart();

		}



	} // !while isOpen

	return 0;
}