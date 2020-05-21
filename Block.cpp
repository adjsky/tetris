#include "Block.h"
#include <random>

Block::Block() : block{} {
	fillBlock();
}

void Block::fillBlock() {
	static std::mt19937 gen{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution die{ 0, 6 };
	int randomNum = die(gen);
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 2; k++) {
			if (points[randomNum][i][k]) {
				sf::RectangleShape piece{};
				piece.setSize(sf::Vector2f(pieceSize, pieceSize));
				piece.setPosition(sf::Vector2f((k + (GRIDWIDTH / 2)) * pieceSize, i * pieceSize));
				piece.setFillColor(sf::Color::Red);
				block.push_back(piece);
			}
		}
	}
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const sf::RectangleShape& piece : block) {
		target.draw(piece);
	}
}

void Block::clearBlock() {
	block.clear();
}

bool Block::check(const mat_t& mat) {
	for (const sf::RectangleShape& piece : block) {
		sf::Vector2f pos{ piece.getPosition() };
		int posY = pos.y / pieceSize;
		int posX = pos.x / pieceSize;
		if (mat[posY][posX] || posX > GRIDWIDTH - 1 || posX < 0 || posY > GRIDHEIGHT) {
			return false;
		}
	}
	return true;
}

void Block::saveBlock() {
	prevBlock = block;
}

void Block::swapBlocks() {
	block = prevBlock;
}

void Block::move(sf::Vector2f dir) {
	for (sf::RectangleShape& piece : block) {
		piece.move(dir);
	}
}

void Block::moveAbsolute(sf::Vector2f dir) {
	for (sf::RectangleShape& piece : block) {
		piece.setPosition(dir);
	}
}

int Block::getPiecesCount() {
	return block.size();
}

sf::RectangleShape& Block::operator[] (int index) {
	return block[index];
}