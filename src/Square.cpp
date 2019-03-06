#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Square.h"
#include "Tile.h"


using namespace std;

Square::Square (int row, int col, string symbol, string multiplier)
{
	_row = row, _col = col, _symbol = symbol, _multiplier = multiplier;
	_hasTile = false;
}

Square::~Square()
{
	if(_hasTile){
		delete _tile;
	}
}

string Square::getValue()
{
	string temp = "";
	if(_hasTile){
		if(_tile->isBlank()){
			temp += _tile->getUse();
			cout << temp << endl;
			return temp;
		}
		else{
			temp += _tile->getLetter();
			return temp;
		}
	}
	return _symbol;
}

string Square::valueForBoard()
{
	if(_hasTile){
		string temp = "";
		if(_tile->isBlank()){
			temp += _tile->getUse();
			temp += "0 ";
			return temp;
		}
		stringstream ss;
		ss << _tile->getPoints();
		ss >> temp;
		temp = _tile->getLetter() + temp;
		if(temp == "Z10"){
			return temp;
		}
		else{
			return temp + " ";
		}
		

	}
	return _symbol;

}

void Square::setValue(Tile *t)
{
	_tile = t;
	_hasTile = true;
}

int Square::returnPoints()
{
	return _tile->getPoints();
}

string Square::getMultiplier()
{
	return _multiplier;
}

bool Square::occupied()
{
	if(_hasTile)
		return true;
	else
		return false;
}