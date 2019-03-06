/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <string>
#include "Square.h"
#include "Dictionary.h"
#include "Tile.h"

class Board {
public:
	Board (std::string board_file_name);
	~Board();
	std::vector<std::string> allWords(int row, int col, char dir, int& score, std::vector<Tile*>& usedTiles);
	std::string vertWord(Tile* t, int row, int col, int& points);
	std::string horizWord(Tile* t, int row, int col, int& points);
	void setFirstMove(bool b);
	bool getFirstMove();
	int getRowSize();
	int getColSize();
	int getStartX();
	int getStartY();
	
	std::vector<std::vector <Square*> > boardVect;
	

	// What else will this need?

private:
	bool isFirstMove;
	int _x; 
	int _y;
	int _startx;
	int _starty;
	//make get functions for _x,_y,_startx,_starty
	// What else will this need?

};


#endif /* BOARD_H_ */
