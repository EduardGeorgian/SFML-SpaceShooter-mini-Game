#pragma once

#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>


#define M_PI 3.14159265358979323846


class StartButton {
private:
	sf::RectangleShape shape;
	sf::Text buttonText;
	sf::Font font;
public:
	StartButton(float x, float y, float width, float height, const std::string& text);
	bool isClicked(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getShape();
	sf::Text getText();
	void changeText(std::string text);
	void resetAppearence();
};

class ExitButton {
private:
	sf::RectangleShape shape;
	sf::Text buttonText;
	sf::Font font;
public:
	ExitButton(float x, float y, float width, float height, const std::string& text);
	bool isClicked(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

class PauseButton :public StartButton {
public:
	PauseButton(float x, float y, float width, float height, const std::string& text);
	bool isClicked(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};



class Player {
private:
	sf::RectangleShape spaceShip;
public:
	Player(float x, float y, float width, float height,sf::Texture & texture);
	void draw(sf::RenderWindow& window);
	void rotateRight(float rPos);
	void rotateLeft(float rPos);
	sf::RectangleShape getSpaceShip();
	sf::Vector2f getTipPosition()
	{
		sf::FloatRect bounds = spaceShip.getGlobalBounds();
		sf::Vector2f unrotatedtipPosition(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2); // Center of the spaceship
		float rotation = spaceShip.getRotation();
		float rotationRad = rotation * (M_PI / 180.0);
		float rotatedX = spaceShip.getPosition().x + (unrotatedtipPosition.x - spaceShip.getPosition().x) * cos(rotationRad) - (unrotatedtipPosition.y - spaceShip.getPosition().y) * sin(rotationRad);
		float rotatedY = spaceShip.getPosition().y + (unrotatedtipPosition.x - spaceShip.getPosition().x) * sin(rotationRad) + (unrotatedtipPosition.y - spaceShip.getPosition().y) * cos(rotationRad);
		return sf::Vector2f(rotatedX, rotatedY);
	}

	float getRotation() const
	{
		return this->spaceShip.getRotation();
	};
	sf::FloatRect resizeGlobalBounds();



	void moveRight(float pos);
	void moveLeft(float pos);
	void moveUp(float pos);
	void moveDown(float pos);
};


class Ammunition {
public:
	sf::CircleShape shape;
	Ammunition(Player spaceShip);
	void draw(sf::RenderWindow& window);
	sf::CircleShape getCircle();
	void updateAmo(Player spaceShip, sf::RenderWindow& window);
	void moveAmo(Player spaceShip, sf::RenderWindow& window);
	bool isOutOfScreen(sf::RenderWindow& window);
};


void moveEnemies(sf::Vector2f playerPos, sf::RectangleShape& enemy);

void moveRoundEnemies(sf::Vector2f playerPos, sf::CircleShape& enemy);

bool collisionPlayerObstacle(sf::FloatRect enemyGlobalBounds, Player player);



class lossScreen {
private:
	sf::Text text;
	sf::Font font;
public:
	lossScreen(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};



class RetryButton : public StartButton {
public:
	RetryButton(float x, float y, float width, float height, const std::string& text):StartButton(x,y,width,height,text){}
	bool isClicked(const sf::RenderWindow& window);
	void draw( sf::RenderWindow& window);

	
};




class Explosion {
public:
	sf::Vector2f position;
	float duration=1.f;  // How long the explosion should last (in seconds)
	sf::Sprite sprite;
};



float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);



