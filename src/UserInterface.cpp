#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include "Dictionary.h"
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Square.h"
#include "UserInterface.h"

using namespace std;

UserInterface::UserInterface()
{
	_turn = 0;
}

UserInterface::~UserInterface()
{
	for(unsigned int i = 0; i < players.size(); i++){
		delete players[i];
	}
}

void UserInterface::createNewPlayers(Bag& bag, int numTiles){
	string dummy;
	cout << "Please enter the number of players (1-8): ";
	cin >> _numPlayers;
	while(1){
		if(cin.fail() ||_numPlayers < 1 || _numPlayers > 8){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid number of players." << endl;
			cout << "Please enter the number of players (1-8): ";
			cin >> _numPlayers;
		}
		else{
			break;
		}
	}
	players.resize(_numPlayers);
	for(int i = 0; i < _numPlayers; i++){
		cout << "Enter the name of player ";
		cout << i+1;
		cout << ": ";
		cin >> _playerName;
		getline(cin, dummy);
		players[i] = new Player(_playerName, 0, numTiles);
		players[i]->getTiles(bag.drawTiles(numTiles));
	}
}

void UserInterface::switchTurns()
{
	cout << "\n";
	if(_turn == _numPlayers-1)
		_turn = 0;
	else
		_turn++;
}

void UserInterface::printBoard(Board& board)
{
	cout << "   ";
	for(int i = 1; i <= board.getRowSize(); i++){
		if(i >= 10){
			cout << i << "  ";
		}
		else{
			cout << i << "   ";
		}
		
	}
	cout << endl;
	for (int i = 0; i < board.getRowSize(); i++){
		if(i >= 9){
			cout << i+1 << " ";
		}
		else{
			cout << i+1 << "  ";
		}
		for(int j = 0; j < board.getColSize(); j++){
			cout << board.boardVect[i][j]->valueForBoard() << " ";
		}
		cout << endl;
	}
	cout << "\n";
}

void UserInterface::printTiles()
{
	cout << players[_turn]->getName() << "'s tiles: ";
	for(unsigned int i = 0; i < players[_turn]->_playerTiles.size(); i++){
		cout << "["<< players[_turn]->_playerTiles[i]->getLetter() << ", "
		<< players[_turn]->_playerTiles[i]->getPoints() << "]" << " ";
	}
	cout << endl;
}

string UserInterface::getMove()
{
	cout << "to pass your turn, type PASS." << endl;
	cout << "To discard tiles, type EXCHANGE, followed by a string of those tiles." << endl;
	cout << "To place a word, type PLACE, followed by the following: " << endl;
   	cout << "  first, either a | or - for vertical/horizontal placement;" << endl;
   	cout << "  second, the row (from the top), the column (from the left)," << endl;
  	cout << "  third, a sequence of letters to place;" << endl;
   	cout << "  to use a blank tile, type ? followed by the letter you want to use it for." << endl;
   	
   	getline(cin, line);
   	return line;

}

void UserInterface::printScore()
{
	cout << "CURRENT SCORE:" << endl;
	for(int i = 0; i < _numPlayers; i++){
		cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
	}
}

void UserInterface::printTurn()
{
	cout << players[_turn]->getName() << ", it is your turn!" << endl;
}

int UserInterface::getTurn()
{
	return _turn;
}

void UserInterface::endGame()
{
	int totScore = 0;
	int pos = 0;
	int max = 0;
	if(players[_turn]->getHandSize() == 0){
		for(unsigned int i = 0; i < players.size(); i++){
			players[i]->subtractScore(players[i]->getHandScore());
			totScore += players[i]->getHandScore();
		}
		players[_turn]->addScore(totScore);
	}
	cout << "FINAL SCORE:" << endl;
	for(int i = 0; i < _numPlayers; i++){
		if(players[i]->getScore() >= max){
			max = players[i]->getScore();
			pos = i;
		}
		cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
	}
	cout << "THE WINNER IS: " << players[pos]->getName();
	for(int i = 0; i < _numPlayers; i++){
		if(i == pos)
			continue;
		else if(players[i]->getScore() == max){
			cout << ", " << players[i]->getName();
		}
	}
	cout << endl;
}