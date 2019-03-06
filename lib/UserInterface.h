#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_
#include <vector>
#include <string>
#include "Player.h"
#include "Bag.h"
#include "Board.h"
#include "Dictionary.h"

class UserInterface {
public:
	UserInterface();
	~UserInterface();
	void createNewPlayers(Bag& bag, int numTiles);
	void switchTurns();
	void printBoard(Board& board);
	void printTiles();
	int getTurn();
	std::string getMove();
	void printScore();
	void printTurn();
	void endGame();
	std::vector<Player*> players;
	

private:
	int _numPlayers;
	int _turn;
	std::string _playerName;
	std::string line;
};


#endif /* USERINTERFACE_H_ */