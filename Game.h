#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include "Block.h"
#include "Variables.h"



class Game {
public:
	Game();
public:
	void start();
	void handleEvents();
	void render();
	void update();
	void restartWave();
	void clearLine();
	void restartGame();
	void clearMat();

private:
	int score;
	sf::Font font;
	sf::Text scoreboard;
	float dropDelay;
	sf::RenderWindow window;
	mat_t mat;
	Block player;
};