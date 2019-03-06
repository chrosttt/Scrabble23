/*
 * Scrabble.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "Dictionary.h"
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Square.h"
#include "UserInterface.h"

using namespace std;

void gamePlay(Dictionary& dict, Board& board, Bag& bag, int numTiles);
bool onFirstTile(int row, int col, char dir, string word, Board& board);


void readConfigFile (string config_file_name,
					 string & dictionary_file_name,
					 string & board_file_name,
					 string & bag_file_name,
					 unsigned int & hand_size)
{
	ifstream configFile (config_file_name.c_str());
	string line;
    bool number = false, hasBoard = false, hasTiles = false, hasDict = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name);
	while (getline (configFile, line))
	{
		stringstream ss (line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
			{ ss >> hand_size; number = true; }
		else if (parameter == "BOARD:")
		    { ss >> board_file_name; hasBoard = true; }
		else if (parameter == "TILES:")
			{ ss >> bag_file_name; hasTiles = true; }
		else if (parameter == "DICTIONARY:")
			{ ss >> dictionary_file_name; hasDict = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!hasBoard)
		throw invalid_argument("Board file name not specified in config file");
	if (!hasTiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!hasDict)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int nargs, char **args)
{
	if (nargs < 2 || nargs > 2)
		cout << "Usage: Scrabble <config-filename>\n";
	try {
		string dictionaryFileName, boardFileName, bagFileName;
		unsigned int numTiles;

		readConfigFile (args[1],
						dictionaryFileName, boardFileName, bagFileName,
						numTiles);

		Dictionary dict (dictionaryFileName);
		Board board (boardFileName);
		Bag bag (bagFileName, 794); // second argument is random seed
		gamePlay(dict, board, bag, numTiles);

		// Good luck!

		return 0;
	}
	catch (invalid_argument & e)
	{ cout << "Fatal Error! " << e.what(); }

	return 1;
}

void gamePlay(Dictionary& dict, Board& board, Bag& bag, int numTiles)
{
	stringstream ss;
	string move, word;
	char dir;
	int r = 0; 
	int c = 0;
	int pos = -1;
	unsigned int counter = 0;
	bool hasTile = true;
	bool firstMove = true;
	bool isValid = true;
	UserInterface UI;
	UI.createNewPlayers(bag, numTiles);
	
	while((bag.tilesRemaining() > 0 || UI.players[UI.getTurn()]->getHandSize() != 0)
		&& (counter != UI.players.size())){
		ss.clear();
		ss.str("");
		UI.printTurn();
		UI.printScore();
		UI.printBoard(board);
		UI.printTiles();
		string line = UI.getMove();
		ss << line;
		ss >> move;
		if(move == "PASS"){
			counter++;
			UI.switchTurns();
		}
		else if(move == "EXCHANGE"){
			counter = 0;
			ss >> word;
			if(ss.fail()){
				cout << "Please enter the right number of parameters.";
				cout << "\n\n";
				continue;
			}
			else{
				for(unsigned int i = 0; i < word.length(); i++){
					word[i] = toupper(word[i]);
				}
			}
			for(unsigned int i = 0; i < word.length(); i++){
				if(!UI.players[UI.getTurn()]->findTile(word[i],pos)){
					cout << "You do not have this tile. Please try again!";
					cout << "\n\n";
					hasTile = false;
					break;
				}
			}
			pos = -1;
			if(!hasTile){
				hasTile = true;
				continue;
			}
			UI.players[UI.getTurn()]->executeExchangeMove(bag, word);
			UI.switchTurns();
		}
		else if (move == "PLACE"){
			counter = 0;
			int numBlanks = 0;
			ss >> dir >> r >> c >> word;
			if(ss.fail()){
				cout << "Command was malformed. Please try another move.";
				cout << "\n\n";
				continue;
			}
			else{
				for(unsigned int i = 0; i < word.length(); i++){
					if(word[i] == '?')
						numBlanks++;
					else
						word[i] = toupper(word[i]);
				}
			}
			if((dir == '-' && (c-1 - numBlanks + (int)word.length() > board.getColSize())) ||
			(dir == '|' && (r-1 - numBlanks + (int)word.length() > board.getRowSize()))) {
				cout << "One or more of your tiles would end up out of bounds. ";
				cout << "Please try another move." << "\n\n";
				continue;
			}
			if(firstMove && !onFirstTile(r-1,c-1,dir,word,board)){
				cout << "First move must start on the starting square. ";
				cout << "Please try another move." << "\n\n";
				continue;
			}
			if(board.boardVect[r-1][c-1]->occupied()){
				cout << "A tile already exists here! Please enter a different position.";
				cout << "\n\n";
				continue;
			}
			for(unsigned int i = 0; i < word.length(); i++){
				if(i != 0 && word[i-1] == '?'){
					continue;
				}
				if(!UI.players[UI.getTurn()]->findTile(word[i], pos)){
					cout << "You do not have this tile. Please try again!";
					cout << "\n\n";
					hasTile = false;
					break;
				}
			}
			pos = -1;
			if(!hasTile){
				hasTile = true;
				continue;
			}
			isValid = UI.players[UI.getTurn()]->executePlaceMove(bag,dict,board,dir,r,c,word);
			if(!isValid) continue;
			firstMove = false;
			UI.switchTurns();
		}
		else{
			cout << "Did not recognize your command. Please try another move!";
			cout << "\n\n";
		}
	}
	UI.endGame();
}

bool onFirstTile(int row, int col, char dir, string word, Board& board)
{
	for(int i = 0; i < (int)word.length(); i++){
		if(dir == '|'){
			if(row + i == board.getStartY() && col == board.getStartX())
				return true;
		}
		else if (dir == '-'){
			if(col + i == board.getStartX() && row == board.getStartY())
				return true;
		}
	}
	return false;
}