#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "Square.h"

using namespace std;

Player::Player(string name, int score, int numTiles)
{
	_name = name;
	_score = score;
	_numTiles = numTiles;
}

Player::~Player()
{
	for(unsigned int i = 0; i < _playerTiles.size(); i++){
		delete _playerTiles[i];
	}
}

string Player::getName()
{
	return _name;
}

void Player::getTiles(set<Tile*> tileSet)
{
	for (set<Tile*>::iterator it = tileSet.begin(); it != tileSet.end(); it++){
		_playerTiles.push_back(*it);
	}
		
}

void Player::useTile(char c)
{
	for(unsigned int i = 0; i < _playerTiles.size(); i++){
		if(c == _playerTiles[i]->getLetter()){
			_playerTiles.erase(_playerTiles.begin() + i);
			break;
		}
	}
}

void Player::exchangeTile(char c, Bag& bag)
{
	for(unsigned int i = 0; i < _playerTiles.size(); i++){
		if(c == _playerTiles[i]->getLetter()){
			bag.addTile(_playerTiles[i]);
			_playerTiles.erase(_playerTiles.begin() + i);
			break;
		}
	}
}

bool Player::findTile(char c, int& pos)
{
	for(int i = 0; i < (int)_playerTiles.size(); i++){
		if(i == pos)
			continue;
		if(c == _playerTiles[i]->getLetter()){
			pos = i;
			return true;
		}
	}
		return false;

}

void Player::returnTile(char c, vector<Tile*>& usedTiles)
{
	for(int i = 0; i < (int)_playerTiles.size(); i++){
		if (c == _playerTiles[i]->getLetter()){
			usedTiles.push_back(_playerTiles[i]);
			return;
		}
	}
}

void Player::addScore(int score)
{
	_score += score;
}

void Player::subtractScore(int score)
{
	_score -= score;
}

int Player::getScore()
{
	return _score;
}

int Player::getHandSize()
{
	return _playerTiles.size();
}

int Player::getHandScore()
{
	int tilesScore = 0;
	for(unsigned int i = 0; i < _playerTiles.size(); i++){
		tilesScore += _playerTiles[i]->getPoints();
	}
	return tilesScore;
}
//EXCHANGE command, returns tiles to bag first, then draws equal number back
void Player::executeExchangeMove(Bag& bag, std::string word)
{
	for(int i = 0; i < (int)word.length(); i++){
		this->exchangeTile(word[i], bag);
	}
	this->getTiles(bag.drawTiles(word.length()));
}

/*this function encapsulates everything that must happen in a PLACE command
calls a function to determine what words are created, then checks those
against the dictionary. If the move is valid, the player's score is incremented
and the tiles are placed in their proper spot on the board */
bool Player::executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word)
{
	vector<string> words;
	vector<Tile*> usedTiles;
	int score = 0;
	for(unsigned int i = 0; i < word.length(); i++){
		returnTile(word[i], usedTiles);
		if (usedTiles[usedTiles.size()-1]->isBlank() && i+1 < word.length()){
			usedTiles[usedTiles.size()-1]->useAs(word[i+1]);
			i++;
		}
	}

	bool isValid = true;
	
	words = board.allWords(row,col,dir,score,usedTiles);

	for(unsigned int i = 0; i < words.size(); i++){
		for(unsigned int j = 0; j < words[i].length(); j++){
			(words[i])[j] = tolower((words[i])[j]);
		}
	}
	
	if(words.empty()){
		cout << "At least one tile must be adjacent to other tiles on the board." << endl;
		return false;
	}

	for(unsigned int i = 0; i < words.size(); i++){
		isValid = dict.checkValid(words[i]);
		if(!isValid){
			cout << words[i] << " is invalid. Please try again." << endl;
			return false;
		}
	}
	if((int)usedTiles.size() == _numTiles){
		score += 50;
	}
	this->addScore(score);
	cout << "Score for this round: " << score << endl;
	unsigned int i = 0;
	bool isOccupied = false;
	while(i < usedTiles.size()){
		isOccupied = board.boardVect[row-1][col-1]->occupied();
		if(dir == '-'){
			if(!isOccupied){
				board.boardVect[row-1][col-1]->setValue(usedTiles[i]);
				this->useTile(usedTiles[i]->getLetter());
				i++;
			}
			col++;
		}
		else if(dir == '|'){
			if(!isOccupied){
				board.boardVect[row-1][col-1]->setValue(usedTiles[i]);
				this->useTile(usedTiles[i]->getLetter());
				i++;
			}
			row++;
		}
	}
	if((int)usedTiles.size() > bag.tilesRemaining()){
		this->getTiles(bag.drawTiles(bag.tilesRemaining()));
	}
	else{
		this->getTiles(bag.drawTiles(usedTiles.size()));
	}
	board.setFirstMove(false);
	return true;
}