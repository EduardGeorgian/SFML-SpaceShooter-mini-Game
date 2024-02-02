#include "Shooter.h"
#include <sstream>
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_LOST,
};


int main() {

    srand(time(NULL));
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game");
    int startButtonResetCount = 0;
    int aah = 0;
    sf::Clock elapsedClock;
    sf::Clock soundClock;
    float soundInterval = 0.5f;
    float MIN_SPAWN_DISTANCE = 50.f;

    sf::SoundBuffer explosionBuffer;
    if (!explosionBuffer.loadFromFile("D:/C++Games/SFML-shooter/SFML-shooter/426439__filipex2000__explosion-1.ogg"))
    {
        std::cout << "ERROR LOADING SOUND FILE FOR shootBuffer";
    }
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionBuffer);
    

   


    sf::Font fontScor;
    if (!fontScor.loadFromFile("Milk Mango.ttf"))
    {
        std::cout << "ERROR: font not found";
    }



    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("C:/Users/edied/Downloads/png-transparent-brown-rock-asteroid-belt-meteoroid-meteor-rock-astronomical-object-outcrop-removebg-preview.png"))
    {
        std::cout<<"ERROR LOADING TEXTURE";
    }

    sf::Texture roundEnemyTexture;
    if (!roundEnemyTexture.loadFromFile("C:/Users/edied/Downloads/meteorit.png"))
    {
        std::cout << "ERROR LOADING TEXTURE";
    }



    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/edied/Downloads/png-transparent-brown-and-black-game-item-illustration-space-shooting-spacecraft-sprite-computer-icons-spaceship-game-symmetry-video-game-thumbnail-removebg-preview.png"))
    {
        std::cout << "ERROR LOADING TEXTURE FOR PLAYER";
    }


    sf::Texture explosionTexture;
    if (!explosionTexture.loadFromFile("C:/Users/edied/Downloads/png-transparent-explosion-fireball-image-file-formats-orange-explosion-removebg-preview.png"))
    {
        std::cout << "ERROR LOADING EXPLOSION TEXTURE";
    }

    sf::Sprite explosionSprite(explosionTexture);

    std::vector<Explosion> explosions;


    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/C++Games/SFML-shooter/SFML-shooter/Images/0d86db583c7b7effafe8d6b4dbd56f83.jpg"))
    {
        std::cout << "ERROR LOADING BACKGROUND TEXTURE" << std::endl;
    }

    sf::Sprite backgroundSprite(backgroundTexture);



    sf::Text scoreText;
    scoreText.setFont(fontScor);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getPosition().x / 2, 10);


    int SCORE = 0;
    std::stringstream ss;

    // Set the initial game state to MENU
    GameState gameState = MENU;
    sf::Vector2i windowPos = window.getPosition();

    StartButton startButton(350, 300, 100, 50, "Start");
    ExitButton exitButton(350, 400, 100, 50, "Exit");
    PauseButton pauseButton(10, 10, 100, 50, "Pause");
    RetryButton retryButton(window.getPosition().x / 2+60, window.getPosition().y+500 / 2,100,50,"Retry");



    lossScreen loss(window);

    Player player1(300, 300, 100, 50, texture);
    Ammunition laser(player1);
    sf::Vector2f projectileVelocity;
    float projectileSpeed = 400.0f;
    sf::Clock frameClock;
    float rPos = 15.f;
    float moveSpeed = 5.f;

    sf::Clock explosionClock;


    sf::RectangleShape enemy;
    sf::CircleShape enemy2;
    enemy2.setRadius(30);
   /* enemy.setFillColor(sf::Color::Cyan);*/
    enemy.setSize(sf::Vector2f(50.f,50.f));
    enemy.setTexture(&enemyTexture);
 
    enemy2.setTexture(&roundEnemyTexture);

    
    
    std::vector<sf::RectangleShape> enemies;
    std::vector<sf::CircleShape> roundEnemies;

    int spawnCounter = 0;
    sf::Clock spawnTimer;
    // Main game loop

    while (window.isOpen()) {
       
        sf::Event event;
        float elapsedTime = elapsedClock.restart().asSeconds();
        while (window.pollEvent(event)) {
            // Handle events based on the current game state
            switch (gameState) {
            case MENU:
                // Handle menu events
                if (startButton.isClicked(window))
                {
                    if (startButtonResetCount != 0)
                    {
                        startButton.resetAppearence();
                    }
                    gameState = PLAYING;
               
                }
                else
                    if (exitButton.isClicked(window))
                    {
                        window.close();
                    }
                break;

            case PLAYING:
                // Handle playing events
                
                if (pauseButton.isClicked(window))
                {
                    startButton.changeText("Resume");
                    startButtonResetCount = 1;
                    gameState = MENU;
                    
                }

                //PLAYER MOVEMENT
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player1.moveRight(moveSpeed);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player1.moveLeft(moveSpeed);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    player1.moveUp(moveSpeed);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    player1.moveDown(moveSpeed);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    player1.rotateRight(rPos);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    player1.rotateLeft(rPos);
                }
               
                if (spawnTimer.getElapsedTime().asMilliseconds() >= 5) {
                    if (spawnCounter < 20)
                    {
                        spawnCounter++;
                    }
                    if (spawnCounter >= 20 && enemies.size() < 10 && roundEnemies.size() <10)
                    {
                        enemy.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
                        enemies.push_back(sf::RectangleShape(enemy));
                        enemy2.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
                        roundEnemies.push_back(sf::CircleShape(enemy2));
                        spawnCounter = 0;
                    }
                    spawnTimer.restart();
                }
               


                break;

            case PAUSED:
                // Handle paused events
                break;

            case GAME_LOST:
               
                break;
                // Add cases for other game states as needed

            default:
                break;
            }

            if (event.type == sf::Event::Closed) {
                // Close the window when the close button is clicked
                window.close();
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        // Update and draw game elements based on the current game state
        switch (gameState) {
        case MENU:
            // Draw menu elements
            startButton.draw(window);
            exitButton.draw(window);
            break;

        case PLAYING:
            // Update and draw game elements
            pauseButton.draw(window);
            for (size_t i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].getGlobalBounds() != player1.resizeGlobalBounds())
                {
                    window.draw(enemies[i]);
                    moveEnemies(player1.getSpaceShip().getPosition(), enemies[i]);
                }
                
            }
            for (size_t k = 0; k < roundEnemies.size(); k++)
            {
                if (roundEnemies[k].getGlobalBounds() != player1.resizeGlobalBounds())
                {
                    window.draw(roundEnemies[k]);
                    moveRoundEnemies(player1.getSpaceShip().getPosition(), roundEnemies[k]);
                }
              
                
            }
            
            //obstacle hit detection
            for (auto j = enemies.begin(); j != enemies.end();) {
                if (laser.getCircle().getGlobalBounds().intersects(j->getGlobalBounds())) {
                    sf::Vector2f obstaclePosition = j->getPosition() + sf::Vector2f(-30.f, -20.f);
                    Explosion newExplosion;
                    newExplosion.position = obstaclePosition;
                    newExplosion.duration = 0.2f;  // Adjust the duration as needed
                    newExplosion.sprite.setTexture(explosionTexture);
                    newExplosion.sprite.setPosition(obstaclePosition);
                    newExplosion.sprite.setScale(0.3f, 0.3f);
                    explosions.push_back(newExplosion);
                    aah = 1;
                    // Remove the enemy
                    j = enemies.erase(j);
                    SCORE++;
                    explosionSound.play();
                }
                else {
                    ++j;  // Increment only if there was no erasure
                }
            }

            /*elapsedClock.restart();
            for (size_t i = 0; i < explosions.size(); i++) {
                window.draw(explosions[i].sprite);
                explosions[i].duration -= elapsedTime;

                if (explosions[i].duration <= 0.0f) {
                    explosions.erase(explosions.begin() + i);
                    i--;
                }
            }*/

            for (auto it = roundEnemies.begin(); it != roundEnemies.end();)
            {
                
                
                if (laser.getCircle().getGlobalBounds().intersects(it->getGlobalBounds())) {
                    sf::Vector2f obstaclePosition = it->getPosition() + sf::Vector2f(-30.f, -20.f);
                    Explosion newExplosion;
                    newExplosion.position = obstaclePosition;
                    newExplosion.duration = 0.2f;  // Adjust the duration as needed
                    newExplosion.sprite.setTexture(explosionTexture);
                    newExplosion.sprite.setPosition(obstaclePosition);
                    newExplosion.sprite.setScale(0.3f, 0.3f);
                    explosions.push_back(newExplosion);
                    aah = 1;
                    // Remove the enemy
                    it = roundEnemies.erase(it);
                    SCORE++;
                    explosionSound.play();
                }
                else {
                    ++it;  // Increment only if there was no erasure
                }
            }
            explosionSound.setVolume(50);
            elapsedClock.restart();
            for (size_t i = 0; i < explosions.size(); i++) {
                window.draw(explosions[i].sprite);
                explosions[i].duration -= elapsedTime;
              

                if (explosions[i].duration <= 0.0f) {
                    explosions.erase(explosions.begin() + i);
                    i--;
                }
            }

          
            for (size_t j = 0; j < enemies.size(); j++)
            {
                if (collisionPlayerObstacle(enemies[j].getGlobalBounds(),player1))
                {
                    std::cout << "COLLISION WITH ENEMY";
                    gameState = GAME_LOST;
                }
            }

            for (size_t l = 0; l < roundEnemies.size(); l++)
            {
                if (collisionPlayerObstacle(roundEnemies[l].getGlobalBounds(),player1))
                {

                    std::cout << "COLLISION WITH ENEMY";
                    gameState = GAME_LOST;
                }
            }
            

           

            player1.draw(window);
            laser.draw(window);
            laser.updateAmo(player1, window);
            laser.moveAmo(player1, window);
            laser.updateAmo(player1, window);
           
            ss.str("");  // Clear the stringstream
            ss << "Score: " << SCORE;
            scoreText.setString(ss.str());

            window.draw(scoreText);

            break;

        case PAUSED:
            // Draw paused screen
            break;

            // Add cases for other game states as needed

        case GAME_LOST:
            //draw Loss screen
            loss.draw(window);
            retryButton.draw(window);
            if (retryButton.isClicked(window) != 0)
            {
                gameState = PLAYING;
                SCORE = 0;
                enemies.clear();
                roundEnemies.clear();
            }

            break;

        default:
            break;
        }
       




        window.display();
    }

    return 0;
}

