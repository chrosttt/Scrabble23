#ifndef SQUARE_H_
#define SQUARE_H_
#include <string>
#include "Tile.h"

class Square {
public:
	Square (int row, int col, std::string symbol, std::string multiplier);
	~Square();
	std::string getValue();
	std::string valueForBoard();
	void setValue(Tile *t);
	int returnPoints();
	std::string getMultiplier();
	bool occupied();

	private:
	int _row, _col;
	Tile* _tile;
	bool _hasTile;
	std::string _symbol;
	std::string _multiplier;
};


#endif /* SQUARE_H_ */