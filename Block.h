#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Variables.h"

class Block : public sf::Drawable {
public:
	Block();
    void clearBlock();
    void fillBlock();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void move(sf::Vector2f dir);
	void moveAbsolute(sf::Vector2f dir);
	void swapBlocks();
	void saveBlock();
	int getPiecesCount();
	bool check(const mat_t& mat);
	sf::RectangleShape& operator[] (int index);
	
private:
	std::vector<sf::RectangleShape> prevBlock;
	std::vector<sf::RectangleShape> block;
};
