#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<sstream> //Using it to convert integers to string


int main()
{
	
	//Preparazione
	sf::Event event;
	bool play = true;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
	window.setFramerateLimit(60);


	//Variables
	int ySpeed = 0;
	int xVelocityBall = -3;
	int yVelocityBall = -4;
	int ySpeedPad2 = 0;
	int pad1Score = 0;
	int pad2Score = 0;
	


	//States
	bool upKey = false;
	bool downKey = false;



	//Images
	sf::Texture texPad;
	sf::Texture texBall;
	sf::Texture texBackground;

	if (texPad.loadFromFile("Data/pad.png") == 0)
	{
		return 1;
	}
	if (texBall.loadFromFile("Data/ball.png") == 0)
	{
		return 1;
	}
	if (texBackground.loadFromFile("Data/background.png") == 0)
	{
		return 1;
	}


	//Sounds
	sf::SoundBuffer buffHit;

	if (buffHit.loadFromFile("Data/hit.wav") == 0)
	{
		return 1;
	}

	sf::Sound hit;
	hit.setBuffer(buffHit);
	
	////////Shapes
	//Backround
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&texBackground);

	//Paddle1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&texPad);

	//Paddle2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&texPad);

	//Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(50, 50));
	ball.setPosition(400, 200);
	ball.setTexture(&texBall);

	//Font
	sf::Font font;
	if (font.loadFromFile("Data/arial.ttf") == 0)
	{
		return 1;
	}

	sf::Text score; 
	score.setFont(font);
	score.setCharacterSize(30); 
	score.setColor(sf::Color::Red);
	score.setPosition(350, 10);
	score.setString("0 : 0");

	
	while (play)
	{
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				upKey = true;
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				upKey = false;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				downKey = true;
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				downKey = false;
			}


		}

		//Logic
		if (upKey)
		{
			ySpeed = -5;
		}
		if (downKey)
		{
			ySpeed = 5;
		}
		if (upKey == false && downKey == false)
		{
			ySpeed = 0;
		}
		if (upKey == true && downKey == true)
		{
			ySpeed = 0;
		}


		pad1.move(0, ySpeed);

		//Bordi mappa di gioco
		if (pad1.getPosition().y < 0)
		{
			pad1.setPosition(50, 0);
		}
		if (pad1.getPosition().y > 500)
		{
			pad1.setPosition(50, 500);
		}



		//Pad2 Logic simple AI
		if (ball.getPosition().y < pad2.getPosition().y)
		{
			ySpeedPad2 = -3;
		}
		if (ball.getPosition().y > pad2.getPosition().y)
		{
			ySpeedPad2 = 3;
		}


		pad2.move(0, ySpeedPad2);



		//Logica Palla
		ball.move(xVelocityBall, yVelocityBall);
		
		//Bordi per palla
		if (ball.getPosition().y < 0)
		{
			yVelocityBall =  -yVelocityBall;
		}
		if (ball.getPosition().y > 500)
		{
			yVelocityBall = -yVelocityBall;
		}
		if (ball.getPosition().x < -50)
		{
			pad2Score++;
			ball.setPosition(350, 200);
		}
		if (ball.getPosition().x > 850)
		{
			pad1Score++;


		}

		//Collisione con i pad 1 e 2 /////I global bounds funzionano nello stesso modo dei collider
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true) 
		{
			hit.play();
			xVelocityBall = -xVelocityBall;
		}
		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true)
		{
			hit.play();
			xVelocityBall = -xVelocityBall;
		}




		window.clear();

		window.draw(background);
		
		//Score
		std::stringstream text; 
		text << pad1Score << " : " << pad2Score; 
		score.setString(text.str());

		window.draw(score);

		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);


		window.display();
	}


	return 0;
}
