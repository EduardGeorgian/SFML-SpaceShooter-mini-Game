#include "Shooter.h"


StartButton::StartButton(float x, float y, float width, float height, const std::string& text)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);


	if (!font.loadFromFile("Milk Mango.ttf"))
	{
		std::cout << "ERROR: font not found";
	}

	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(20);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(x + 20, y + 10);

}


sf::RectangleShape StartButton::getShape()
{
	return this->shape;
}

sf::Text StartButton::getText()
{
	return this->buttonText;
}

bool StartButton::isClicked(const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		return shape.getGlobalBounds().contains(mousePos);
	}
	return false;
}

void StartButton::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(buttonText);
}

ExitButton::ExitButton(float x, float y, float width, float height, const std::string& text)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);


	if (!font.loadFromFile("Milk Mango.ttf"))
	{
		std::cout << "ERROR: font not found";
	}

	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(20);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(x + 20, y + 10);

}


bool ExitButton::isClicked(const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		return shape.getGlobalBounds().contains(mousePos);
	}
	return false;
}

void ExitButton::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(buttonText);
}



PauseButton::PauseButton(float x, float y, float width, float height, const std::string& text) :StartButton(x, y, width, height, text) {}

bool PauseButton::isClicked(const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		return this->getShape().getGlobalBounds().contains(mousePos);
	}
	return false;
}

void PauseButton::draw(sf::RenderWindow& window)
{
	window.draw(this->getShape());
	window.draw(this->getText());
}



Player::Player(float x, float y, float width, float height,sf::Texture &texture)
{
	/*spaceShip.setPointCount(4);

	spaceShip.setPoint(0, sf::Vector2f(50, 0));
	spaceShip.setPoint(1, sf::Vector2f(0, 100));
	spaceShip.setPoint(2, sf::Vector2f(50, 75));
	spaceShip.setPoint(3, sf::Vector2f(100, 100));*/
	

	spaceShip.setSize(sf::Vector2f(50.f, 50.f));
	spaceShip.setTexture(&texture);
	spaceShip.setPosition(x + height / 2 + 100, y + width / 2);
	/*spaceShip.setOrigin(spaceShip.getLocalBounds().width / 2, spaceShip.getLocalBounds().height / 2);*/
	spaceShip.setOrigin(spaceShip.getSize() / 2.0f);


}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(spaceShip);
}


//PLAYER MOVEMENT USING WASD
void Player::moveRight(float pos)
{
	this->spaceShip.setPosition(this->spaceShip.getPosition().x + pos,this->spaceShip.getPosition().y);
}
void Player::moveLeft(float pos)
{
	this->spaceShip.setPosition(this->spaceShip.getPosition().x - pos, this->spaceShip.getPosition().y);
}
void Player::moveUp(float pos)
{
	this->spaceShip.setPosition(this->spaceShip.getPosition().x , this->spaceShip.getPosition().y-pos);
}
void Player::moveDown(float pos)
{
	this->spaceShip.setPosition(this->spaceShip.getPosition().x, this->spaceShip.getPosition().y+pos);
}





void Player::rotateRight(float rPos)
{

	spaceShip.rotate(rPos);
}

void Player::rotateLeft(float rPos)
{

	spaceShip.rotate(-rPos);
}

sf::RectangleShape Player::getSpaceShip()
{
	return this->spaceShip;
}

sf::FloatRect Player::resizeGlobalBounds()
{
	sf::FloatRect originalBounds = this->spaceShip.getGlobalBounds();

	float padding = 150.f;

	sf::FloatRect adjustedBounds(
		originalBounds.left - padding,
		originalBounds.top - padding,
		originalBounds.width + 2 * padding,
		originalBounds.height + 2 * padding);

	return adjustedBounds;
}



Ammunition::Ammunition(Player spaceShip)
{
	sf::Texture amoTexture;
	if (!amoTexture.loadFromFile("C:/Users/edied/Downloads/fireBall-removebg-preview.png"))
	{
		std::cout<<"Error loading texture for amo"<<std::endl;
	}
	this->shape.setTexture(&amoTexture);
	
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setRadius(5);
	this->shape.setPosition(spaceShip.getSpaceShip().getPosition()/*+sf::Vector2f(0,-30)*/);
	this->shape.setOrigin(shape.getRadius(), shape.getRadius());
}

void Ammunition::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::CircleShape Ammunition::getCircle()
{
	return this->shape;
}


void Ammunition::updateAmo(Player spaceShip, sf::RenderWindow& window)
{
	if (shape.getPosition().x > 800 || shape.getPosition().x < 0 || shape.getPosition().y>800 || shape.getPosition().y < 0) {
		shape.setPosition(spaceShip.getTipPosition());
	}
}

//void Ammunition::moveAmo(Player spaceShip, sf::RenderWindow& window)
//{
//	sf::Vector2f direction = spaceShip.getTipPosition();
//	/*float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//	if (magnitude >0)
//	{
//		direction /= magnitude;
//		
//	}*/
//	
//	this->shape.move(-direction);
//}

void Ammunition::moveAmo(Player spaceShip, sf::RenderWindow& window)
{
	float rotation = spaceShip.getRotation() - 85.5; // get the player's rotation in degrees
	float speed = 4.f; // replace with the speed you want

	// calculate the direction vector
	sf::Vector2f direction(std::cos(rotation * M_PI / 180.0f), std::sin(rotation * M_PI / 180.0f));

	// normalize the direction vector
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude > 0)
	{
		direction /= magnitude;
	}

	// move the shape
	this->shape.move(direction * speed);
}

bool Ammunition::isOutOfScreen(sf::RenderWindow& window)
{

	if (shape.getPosition().x > 800 || shape.getPosition().x < 0 || shape.getPosition().y>800 || shape.getPosition().y < 0) 
	{
		return 1;
	}
	return 0;
}



void moveEnemies(sf::Vector2f playerPos, sf::RectangleShape& enemy)
{
	sf::Vector2f direction = playerPos - enemy.getPosition();
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction /= magnitude;
	}
	enemy.move(direction * 0.008f);
}

void moveRoundEnemies(sf::Vector2f playerPos, sf::CircleShape& enemy)
{
	sf::Vector2f direction = playerPos - enemy.getPosition();
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction /= magnitude;
	}
	enemy.move(direction * 0.008f);
}


bool collisionPlayerObstacle(sf::FloatRect enemyGlobalBounds, Player player)
{
	if(enemyGlobalBounds.intersects(player.getSpaceShip().getGlobalBounds()))
		return 1;
	else
		return 0;
}


lossScreen::lossScreen(sf::RenderWindow& window) {
	if (!font.loadFromFile("Milk Mango.ttf")) {
		std::cout << "ERROR LOADING FONT FILE";
	}

	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	// Center the text on the screen
	sf::FloatRect textRect = text.getLocalBounds();
	text.setPosition(window.getSize().x/2-150, window.getSize().y/2-100);
	text.setString("GAME OVER");
}



void lossScreen::draw(sf::RenderWindow& window)
{
	window.draw(text);
}


void StartButton::changeText(std::string text)
{
	this->buttonText.setString(text);
	this->buttonText.setScale(0.95f, 0.95f);
	this->buttonText.setPosition(buttonText.getPosition().x - 10, buttonText.getPosition().y);
}

void StartButton::resetAppearence()
{
	this->buttonText.setString("Start");
	this->buttonText.setScale(1.f, 1.f);
	this->buttonText.setPosition(buttonText.getPosition().x + 10, buttonText.getPosition().y);
}
bool RetryButton::isClicked(const sf::RenderWindow& window)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		return this->getShape().getGlobalBounds().contains(mousePos);
	}
	return false;
}



void RetryButton::draw( sf::RenderWindow& window)
{
	window.draw(this->getShape());
	window.draw(this->getText());
}



float distance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	return std::sqrt(dx * dx + dy * dy);
}


