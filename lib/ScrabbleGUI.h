#ifndef SCRABBLEGUI_H
#define SCRABBLEGUI_H
#include "UserInterface.h"
#include "Dictionary.h"
#include "Board.h"
#include "Bag.h"

class ScrabbleGUI {
    
public:
    ScrabbleGUI (std::string fileName);
    ~ScrabbleGUI();
    Dictionary* getDict();
    Board* getBoard();
    Bag* getBag();
    int getHandSize();

private:
 	int hand_size;
 	std::string board_file_name, bag_file_name;
 	std::string dictionaryFileName;
 	Dictionary* _dict;
 	Board* _board;
 	Bag* _bag;
};

#endif