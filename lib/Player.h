#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>
#include <vector>
#include <set>
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "Square.h"

class Player {
public:
	Player(std::string name, int score, int numTiles);
	~Player();
	std::string getName();
	void getTiles(std::set<Tile*>);
	void useTile(char c);
	void exchangeTile(char c, Bag& bag);
	void addScore(int score);
	void subtractScore(int score);
	bool findTile(char c, int& pos);
	void returnTile(char c, std::vector<Tile*>& usedTiles);
	bool executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word);
	void executeExchangeMove(Bag& bag, std::string word);
	int getScore();
	int getHandSize();
	int getHandScore();
	std::vector<Tile*> _playerTiles;

	private:
	int _score;
	int _numTiles;
	std::string _name;
	
};


#endif /* PLAYER_H_ */
