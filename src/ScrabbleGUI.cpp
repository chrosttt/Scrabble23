#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "ScrabbleGUI.h"
#include "Dictionary.h"
#include "Board.h"
#include "Bag.h"

using namespace std;

//Initialize board, bag, and dictionary 
ScrabbleGUI::ScrabbleGUI (std::string fileName)
{
	ifstream configFile (fileName.c_str());
	std::string line;
    bool number = false, hasBoard = false, hasTiles = false, hasDict = false;


	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + fileName);
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
			{ ss >> dictionaryFileName; hasDict = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!hasBoard)
		throw invalid_argument("Board file name not specified in config file");
	if (!hasTiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!hasDict)
		throw invalid_argument("Dictionary file name not specified in config file");
	_dict = new Dictionary(dictionaryFileName);
	_board  = new Board(board_file_name);
	_bag  = new Bag(bag_file_name, time(NULL));
}

ScrabbleGUI::~ScrabbleGUI()
{
	delete _dict;
	delete _board;
	delete _bag;
}

Dictionary* ScrabbleGUI::getDict()
{
	return _dict;
}

Board* ScrabbleGUI::getBoard()
{
	return _board;
}

Bag* ScrabbleGUI::getBag()
{
	return _bag;
}   

int ScrabbleGUI::getHandSize()
{
	return hand_size;
}