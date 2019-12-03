#include <SFML/Graphics.hpp>

#define RAND_DIR (rand() % RAND_MAX) % 2 == 0 ? -1 : 1 

const sf::Uint16 WIDTH = 640;
const sf::Uint16 HEIGHT = 480;

void checkCollision(sf::Sprite &s, sf::Vector2f fPos, sf::FloatRect fSize, sf::Vector2f& dir)
{
	if (fPos.x <= 0 || fPos.x + fSize.width >= WIDTH)
		dir.x = -dir.x;
	if (fPos.y <= 0 || fPos.y + fSize.height >= HEIGHT)
		dir.y = -dir.y;
}

int main(int argc, char* argv[])
{
	srand((unsigned) time(NULL));

	sf::RenderWindow mWindow(sf::VideoMode(WIDTH, HEIGHT), "Bounds Demo", sf::Style::Close);
	mWindow.setFramerateLimit(60);

	sf::Texture tMushroom;
	tMushroom.loadFromFile("res/mushroom.png");


	sf::Sprite sMushroom(tMushroom);
	sf::FloatRect fBounds = sMushroom.getGlobalBounds();
	sMushroom.setPosition(sf::Vector2f(0.5f * (WIDTH - fBounds.width), 0.5f * (HEIGHT - fBounds.height)));
	sMushroom.setColor(sf::Color(255, 255, 0, 255));

	sf::Vector2f fDlt(3.0f, 3.0f);
	sf::Vector2f fPos = sMushroom.getPosition();
	sf::Vector2f fDir;
	int count = 1;

	fDir.x = static_cast<float>(RAND_DIR);
	fDir.y = static_cast<float>(RAND_DIR);

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow.close();
		}

		checkCollision(sMushroom, fPos, fBounds, fDir);

		fPos.x += fDlt.x * fDir.x;
		fPos.y += fDlt.y * fDir.y;

		sMushroom.setPosition(fPos.x, fPos.y);

		mWindow.clear(sf::Color(16, 16, 16, 255));
		mWindow.draw(sMushroom);
		mWindow.display();
	}
	return 0;
}