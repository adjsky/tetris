#include "Game.h"

#include <iostream>

Game::Game() :
	window{ sf::VideoMode(GRIDWIDTH * pieceSize + 200, pieceSize * GRIDHEIGHT), "Tetris", sf::Style::Close},
	dropDelay{ 0.05f }
{
	font.loadFromFile("resources/Roboto-Regular.ttf");
	scoreboard.setString("Score: " + std::to_string(score));
	scoreboard.setCharacterSize(30);
	scoreboard.setFont(font);
	scoreboard.setFillColor(sf::Color::Black);
	scoreboard.setPosition(sf::Vector2f(GRIDWIDTH * pieceSize + 10.0f, 0.0f));
	window.setFramerateLimit(60);
}

void Game::start() {
	sf::Clock clock;
	float timer = 0;
	
	
	while (window.isOpen()) {
		timer += clock.getElapsedTime().asSeconds();
		clock.restart();
		handleEvents();
		if (timer > dropDelay) {
			update();
			timer = 0;
		}
		render();
	}
}

void Game::handleEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window.close();
		}
		else if (e.type == sf::Event::KeyPressed) {
			player.saveBlock();
			if (e.key.code == sf::Keyboard::A) {
				player.move(sf::Vector2f(-pieceSize, 0));
			}
			if (e.key.code == sf::Keyboard::D) {
				player.move(sf::Vector2f(pieceSize, 0));
			}
			if (e.key.code == sf::Keyboard::W) {
				sf::RectangleShape p{ player[1] };
				for (int i = 0; i < 4; i++)
				{
					int x = player[i].getPosition().y - p.getPosition().y;
					int y = player[i].getPosition().x - p.getPosition().x;
					player[i].setPosition(sf::Vector2f(p.getPosition().x - x, p.getPosition().y + y));
				}
			}
			if (!player.check(mat)) {
				player.swapBlocks();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			dropDelay = 0.01f;
		}
		else {
			dropDelay = 0.05f;
		}
	}
}

void Game::update() {
	scoreboard.setString("Score: " + std::to_string(score));
	clearLine();

	player.saveBlock();
	player.move(sf::Vector2f(0, pieceSize));
	if (!player.check(mat)) {
		player.swapBlocks();
		if (player[0].getPosition().y < pieceSize * 4) restartGame(); // check if player's position is on the spawn when it can't move down
		else restartWave();
	}
}

void Game::render() {
	window.clear(sf::Color::White);

	for (int i{ 0 }; i < GRIDHEIGHT; i++) {
		for (int k{ 0 }; k < GRIDWIDTH; k++) {
			if (mat[i][k]) {
				Block block{};
				block.moveAbsolute(sf::Vector2f(k * pieceSize, i * pieceSize));
				window.draw(block);
			}
			else {
				sf::RectangleShape field{ sf::Vector2f(pieceSize, pieceSize) };
				field.setPosition(sf::Vector2f(k * pieceSize, i * pieceSize));
				field.setFillColor(sf::Color::White);
				field.setOutlineColor(sf::Color::Black);
				field.setOutlineThickness(1.0f);
				window.draw(field);
			}	
		}
	}

	window.draw(player);
	
	window.draw(scoreboard);

	window.display();
}

void Game::restartWave() {
	for (int i{ 0 }; i < player.getPiecesCount(); i++) {
		sf::Vector2f pos{ player[i].getPosition() };
		mat[pos.y / pieceSize][pos.x / pieceSize] = 1;
	}
	player.clearBlock();
	player.fillBlock();
}

void Game::clearLine() {
	int k = GRIDHEIGHT - 1;
	for (int i = GRIDHEIGHT - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			if (mat[i][j]) count++;
			mat[k][j] = mat[i][j];
		}
		if (count < GRIDWIDTH) k--;
		else {
			score += 100;
		};
	}
}

void Game::clearMat() {
	for (int i{ 0 }; i < GRIDHEIGHT; i++) {
		for (int k{ 0 }; k < GRIDWIDTH; k++) {
			mat[i][k] = 0;
		}
	}
}

void Game::restartGame() {
	score = 0;
	player.clearBlock();
	player.fillBlock();
	clearMat();
}