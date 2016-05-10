#include "SFML/Graphics.hpp"
#include "cmath"
#include "kf/kf_log.h"
#include "qgf2d/system.h"
#include "qgf2d/anim.h"
#include "fish.h"

using namespace std;
using namespace qgf;
using namespace kf;
using namespace sf;

int playerLives = 1;
int playerSize = 1;
int score = 0;

float speedX = 0;
float speedY = 0;

float sW = 800;
float sH = 600;

float timerFishSpawn = 0;
float timerShark = 0;
float timerJelly = 0;
float timerCrab = 0;

Fish *shark;
Fish *jelly;
Fish *crab;

bool sharkAlive = false;
bool jellyAlive = false;
bool crabAlive = false;

bool activeGame = false;
bool activeMenu = true;
bool activeEnd = false;

void SpriteFlip(Fish* fish)
{
	if (fish->moveX > 0)
	{
		fish->mSprite->setScale(-1, 1);
	}
	else
	{
		fish->mSprite->setScale(1, 1);
	}
}

//box collision deteection function algorithim
bool collision(float centre1x, float centre1y, float width1, float height1, float centre2x, float centre2y, float width2, float height2)
{
	return centre1x - width1 / 2 < centre2x + width2 / 2 &&
		centre1x + width1 / 2 > centre2x - width2 / 2 &&
		centre1y - height1 / 2 < centre2y + height2 / 2 &&
		centre1y + height1 / 2 > centre2y - height2 / 2;
}

int main()
{
	// This sets the working directory to where the executable is.
	initDirectory();

	// Start the KF log system, tell it to log to the console and a file.
	Log::getDefault().addCout();
	Log::getDefault().addFile("base.log");
	kf_log("This is the base qgf2d project");

	// Open a window to draw into. This one is 800 x 600 in 32 bit colour. The string "Base" is the window title.
	RenderWindow window(VideoMode(sW, sH, 32), "Base");

	//load fish textures
	Texture *fish1Texture = new Texture();
	Texture *fish2Texture = new Texture();
	Texture *fish3Texture = new Texture();
	Texture *fish4Texture = new Texture();
	Texture *fish5Texture = new Texture();
	Texture *crabTexture = new Texture();
	Texture *jellyTexture = new Texture();
	Texture *sharkTexture = new Texture();

	//asign textures
	if (!fish1Texture->loadFromFile("data/fish1.png"))
	{
		return EXIT_FAILURE;
	}
	if (!fish2Texture->loadFromFile("data/fish2.png"))
	{
		return EXIT_FAILURE;
	}
	if (!fish3Texture->loadFromFile("data/fish3.png"))
	{
		return EXIT_FAILURE;
	}
	if (!fish4Texture->loadFromFile("data/fish4.png"))
	{
		return EXIT_FAILURE;
	}
	if (!fish5Texture->loadFromFile("data/fish5.png"))
	{
		return EXIT_FAILURE;
	}
	if (!crabTexture->loadFromFile("data/crab.png"))
	{
		return EXIT_FAILURE;
	}
	if (!jellyTexture->loadFromFile("data/jellyFish.png"))
	{
		return EXIT_FAILURE;
	}
	if (!sharkTexture->loadFromFile("data/shark.png"))
	{
		return EXIT_FAILURE;
	}

	// Load a texture from the data directory.
	Texture *backgroundTexture = new Texture();
	if (!backgroundTexture->loadFromFile("data/underwater.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture *startScreenTexture = new Texture();
	if (!startScreenTexture->loadFromFile("data/StartScreen.png"))
	{
		return EXIT_FAILURE;
	}

	Texture *gameOverTexture = new Texture();
	if (!gameOverTexture->loadFromFile("data/GameOver.png"))
	{
		return EXIT_FAILURE;
	}
	
	Texture *playerTexture = new Texture();
	if (!playerTexture->loadFromFile("data/fish.png"))
	{
		return EXIT_FAILURE;
	}

	//create AI fish list
	vector<Fish*> fishAll;

	// Create a sprites
	Sprite *backgroundSprite = new Sprite(*backgroundTexture);

	Sprite *startScreenSprite = new Sprite(*startScreenTexture);

	Sprite *gameOverSprite = new Sprite(*gameOverTexture);

	Sprite *playerSprite = new Sprite(*playerTexture);

	//centre player
	playerSprite->setPosition(400, 300);

	// Scale the sprite so the texture stretches to fit in the window.
	backgroundSprite->scale(sW/backgroundTexture->getSize().x, sH/backgroundTexture->getSize().y);

	// Set up a font for text rendering.
	sf::Font myFont;
	if (!myFont.loadFromFile("data/bluehigh.ttf"))
	{
		return EXIT_FAILURE;
	}

	//score, lives and size text display
	sf::Text *text = new sf::Text();
	text->setFont(myFont);
	text->setPosition(300, 20);

	// The clock is used to keep track of how much time has gone past.
	sf::Clock clock;

	// This is the main game loop. It continues while the window is open.
	while (window.isOpen())
	{
		float deltaT = clock.restart().asSeconds();

		if (activeGame == true)
		{
			timerFishSpawn += deltaT;
			timerShark += deltaT;
			timerCrab += deltaT;
			timerJelly += deltaT;
		}

		// Events are things such as keys being pressed, the window closing, etc.
		// There could be several events waiting for us, so use a loop to process them all.
		Event ev;
		while (window.pollEvent(ev))
		{
			if ((ev.type == Event::Closed) || ((ev.type == Event::KeyPressed) && (ev.key.code == Keyboard::Escape)))
			{
				window.close();
				break;
			}
		}
		int lastScore = score;
		//basic 1-5 fish spawner, roll a random fish number to spawn
		if (activeGame == true)
		{
			if (timerFishSpawn > 2 && fishAll.size() < 8)
			{
				timerFishSpawn = 0;

				int ran = rand() % 5 + 1;

				Fish *temp;

				if (ran == 1)
				{
					temp = new Fish(200, 140, new Sprite(*fish1Texture), 0, false);
				}

				if (ran == 2)
				{
					temp = new Fish(180, 130, new Sprite(*fish2Texture), 1, false);
				}

				if (ran == 3)
				{
					temp = new Fish(160, 120, new Sprite(*fish3Texture), 2, false);
				}

				if (ran == 4)
				{
					temp = new Fish(140, 110, new Sprite(*fish4Texture), 3, false);
				}

				if (ran == 5)
				{
					temp = new Fish(120, 100, new Sprite(*fish5Texture), 4, false);
				}

				temp->mSprite->setPosition((rand() % 2 * sW + 60) - 30, rand() % 500);

				fishAll.push_back(temp);
			}

			//shark spawner
			if (timerShark > 15)
			{
				if (!sharkAlive)
				{
					shark = new Fish(120, 60, new Sprite(*sharkTexture), 10, false);
					fishAll.push_back(shark);
					shark->mSprite->setPosition((rand() % 2 * sW + 60) - 30, rand() % 500);
					sharkAlive = true;
				}
				
				else if (timerShark > 30)
				{
					shark->mDead = true;
					sharkAlive = false;
					timerShark = 0;
				}
			}
			//crab spawner
			if (timerCrab > 10)
			{

				if (!crabAlive)
				{
					crab = new Fish(50, 0, new Sprite(*crabTexture), 5, false);
					fishAll.push_back(crab);
					crab->mSprite->setPosition((rand() % 2 * sW + 60) - 30, 560);
					crabAlive = true;
				}
				
				else if (timerCrab > 30)
				{
					crab->mDead = true;
					crabAlive = false;
					timerCrab = 0;
				}
			}
			//jellyfish spawner
			if (timerJelly > 8)
			{
				if (!jellyAlive)
				{
					jelly = new Fish(140, 50, new Sprite(*jellyTexture), 6, false);
					fishAll.push_back(jelly);
					jelly->mSprite->setPosition((rand() % 2 * sW + 60) - 30, rand() % 500);
					jellyAlive = true;
				}
				
				else if (timerJelly > 16)
				{
					jelly->mDead = true;
					jellyAlive = false;
					timerJelly = 0;
				}
			}
		}
		


		//player controls
		if (Keyboard::isKeyPressed(Keyboard::Space) && activeMenu == true)
		{
			playerSprite->setPosition(400, 300);
			activeMenu = false;
			activeGame = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
			speedX = 200;
			
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			speedX = -200;

		else
			speedX *= (1 - (2 * deltaT));

		if (Keyboard::isKeyPressed(Keyboard::Up))
			speedY = -200;
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			speedY = 200;
		else
			speedY *= (1 - (2 * deltaT));

		//hold left shift to accelerate
		if (((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::Left))) && (Keyboard::isKeyPressed(Keyboard::LShift)))
		{
			speedX *= 2;
		}

		if (((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Down))) && (Keyboard::isKeyPressed(Keyboard::LShift)))
		{
			speedY *= 2;
		}

		playerSprite->move(speedX * deltaT, speedY * deltaT);
		
		//Fish AI behaviours, collision detection and interactions
		for (int i = 0; i < fishAll.size(); i++)
		{
			if (!fishAll[i]->mDead)
			{
				for (int j = 0; j < fishAll.size(); j++)
				{
					if (i == j)
					{
						continue;
					}
					//box collision detection for Ai vs Ai
					if (collision(fishAll[i]->mSprite->getPosition().x, fishAll[i]->mSprite->getPosition().y, fishAll[i]->mSprite->getTexture()->getSize().x * 0.75, fishAll[i]->mSprite->getTexture()->getSize().y * 0.75,
						fishAll[j]->mSprite->getPosition().x, fishAll[j]->mSprite->getPosition().y, fishAll[j]->mSprite->getTexture()->getSize().x * 0.75, fishAll[j]->mSprite->getTexture()->getSize().y * 0.75))
					{
						if (fishAll[i]->mSize > fishAll[j]->mSize)
						{
							fishAll[j]->mDead = true;
							fishAll[j]->mSprite->setColor(sf::Color::Red);
						}
						if (fishAll[i]->mSize < fishAll[j]->mSize)
						{
							fishAll[i]->mDead = true;
							fishAll[i]->mSprite->setColor(sf::Color::Red);
						}
					}
				}
				//box collision detection for player vs Ai
				if (collision(fishAll[i]->mSprite->getPosition().x, fishAll[i]->mSprite->getPosition().y, fishAll[i]->mSprite->getTexture()->getSize().x * 0.75, fishAll[i]->mSprite->getTexture()->getSize().y * 0.75,
					playerSprite->getPosition().x, playerSprite->getPosition().y, playerTexture->getSize().x, playerTexture->getSize().y))
				{
					if (fishAll[i]->mSize >= playerSize)
					{
						playerLives--;
						playerSprite->setPosition(400, 300);
						for (int j = 0; j < fishAll.size(); j++)
						{
							fishAll[j]->mDead = true;
						}
					}
					if (fishAll[i]->mSize < playerSize)
					{
						score += 100;
						fishAll[i]->mDead = true;
					}
				}


				if (fishAll[i] == shark)
				{
					//shark behaviour (move toward player)
				}
				
				if (fishAll[i] == crab)
				{
					//crab behaviour (jump up every so often)
				}
				
				//bounce Ai fish off game screen
				if (fishAll[i]->mSprite->getPosition().x < 0 && fishAll[i]->moveX < 0)
					fishAll[i]->moveX = -fishAll[i]->moveX;
				else if (fishAll[i]->mSprite->getPosition().x > sW && fishAll[i]->moveX > 0)
					fishAll[i]->moveX = -fishAll[i]->moveX;
				if (fishAll[i]->mSprite->getPosition().y < 0 && fishAll[i]->moveY < 0)
					fishAll[i]->moveY = -fishAll[i]->moveY;
				else if (fishAll[i]->mSprite->getPosition().y > sH && fishAll[i]->moveY > 0)
					fishAll[i]->moveY = -fishAll[i]->moveY;

					SpriteFlip(fishAll[i]);
					fishAll[i]->mSprite->move(fishAll[i]->moveX * deltaT, fishAll[i]->moveY *deltaT);
			}
		}
		//delete Ai fish who are set to mDead
		for (int i = 0; i < fishAll.size(); i++)
		{
			if (fishAll[i]->mDead == true)
			{
				delete fishAll[i];
				fishAll[i] = fishAll.back();
				fishAll.pop_back();
				--i;
			}
		}
		
		//adjust player stats
		if (playerLives == 0)
		{
			activeGame = false;
			activeEnd = true;
		}

		if (lastScore / 1000 < score / 1000)
		{
			if (playerSize < 5)
			{
				playerSize++;
			}
			else playerLives++;
		}

		// Clear the window.
		window.clear();
		// Print the game stats and draw the background pictures according to which game state variable is set
		window.draw(*backgroundSprite);
		text->setString("Score: " + std::to_string(score) + " Lives: " + std::to_string(playerLives) +" Size: " + std::to_string(playerSize));
		window.draw(*text);
		window.draw(*playerSprite);
		if (activeMenu == true)
		{
			window.draw(*startScreenSprite);
		}
		if (activeEnd == true)
		{
			window.draw(*gameOverSprite);
		}
		//draw Ai fish
		for (int i = 0; i < fishAll.size(); i++)
		{
			window.draw(*(fishAll[i]->mSprite));
		}
		// Calling display will make the contents of the window appear on screen (before this, it was kept hidden in the back buffer).
		window.display();
	}

	// Clean up
	delete text;
	delete backgroundSprite;
	delete backgroundTexture;
	delete playerSprite;

	return 0;
}

