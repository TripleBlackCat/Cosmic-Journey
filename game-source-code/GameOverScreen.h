#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>

class GameOverScreen
{
    public:
        GameOverScreen();
        void show(sf::RenderWindow& renderWindow);
        ~GameOverScreen();
private:
	sf::Texture _gameOverTexture;
	sf::Font font;
};




#endif