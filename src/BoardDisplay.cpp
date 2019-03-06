#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <iostream>
#include <QString>
#include <string>
#include <vector>
#include <QButtonGroup>
#include "BoardDisplay.h"

BoardDisplay::BoardDisplay(Board* board, UserInterface* UI)
{
	_UI = UI;
	counter = 0;
  	_board = board;
  	_row = -1;
  	_col = -1;
  	
	boardLayout = new QGridLayout();
	boardLayout->setSpacing(0);
	boardLayout->setMargin(0);

	allTiles = new QButtonGroup();
	updateBoard();

	connect(allTiles, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(confirmPressed(QAbstractButton*)));

	setLayout(boardLayout);
}

//Update board based on its state in the backend
void BoardDisplay::updateBoard()
{
	QString temp;

	for(int i = 0; i < _board->getColSize(); i++){
		for(int j = 0; j < _board->getRowSize(); j++){
			if(_board->boardVect[i][j]->occupied()){
				temp = QString::fromStdString(_board->boardVect[i][j]->getValue());
				temp += QString::number(_board->boardVect[i][j]->returnPoints());
				placedTile = new QLabel(temp);
				placedTile->setFrameStyle(QFrame::Panel | QFrame::Raised);
				placedTile->setLineWidth(3);
				placedTile->setStyleSheet("background-color: khaki;");
				placedTile->setAlignment(Qt::AlignCenter);
				boardLayout->addWidget(placedTile,i, j, 1, 1);
				continue;
			}
			else if(_board->boardVect[i][j]->getValue() == "3W "){
				square = new QPushButton("3W");
				square->setStyleSheet("background-color: orange");
			}
			else if(_board->boardVect[i][j]->getValue() == "2W "){
				square = new QPushButton("2W");
				square->setStyleSheet("background-color: pink");
			}
			else if(_board->boardVect[i][j]->getValue() == "3L "){
				square = new QPushButton("3L");
				square->setStyleSheet("background-color: lightgreen");
			}
			else if(_board->boardVect[i][j]->getValue() == "2L "){
				square = new QPushButton("2L");
				square->setStyleSheet("background-color: lightblue");
			}
			else if(_board->boardVect[i][j]->getValue() == "***"){
				square = new QPushButton("*");
				square->setStyleSheet("background-color: pink");
			}
			else{
				square = new QPushButton("");
				square->setStyleSheet("background-color: beige");
			}
			square->setMinimumWidth(35);
			square->setMinimumHeight(35);

			allTiles->addButton(square);
			allTiles->setExclusive(false);
			boardLayout->addWidget(square,i, j, 1, 1);
		}
		_row = -1;
  		_col = -1;
	}

}

//Set row and column of square selected
void BoardDisplay::confirmPressed(QAbstractButton* button)
{
	if(counter > 0){
		resetSquare(tempButton);
	}
	tempButton = button;
	int index = boardLayout->indexOf(button);
	//set square to yellow to denote that it has been selected
	button->setStyleSheet("background-color:yellow;" "font-weight: bold;");
	int row, col, col_span, row_span;
    boardLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
    _row = row;
    _col = col;
    counter++;
}
//reset square to original color when a new one is selected
void BoardDisplay::resetSquare(QAbstractButton* button){
	QString msg = button->text();
	std::string text  = msg.toStdString();
	if(text == "3W"){
		button->setStyleSheet("background-color: orange");
	}
	else if(text == "2W"){
		button->setStyleSheet("background-color: pink");
	}
	else if(text == "3L"){
		button->setStyleSheet("background-color: lightgreen");
	}
	else if(text == "2L"){
		button->setStyleSheet("background-color: lightblue");
	}
	else if(text == "*"){
		button->setStyleSheet("background-color: pink");
	}
	else{
		button->setStyleSheet("background-color: beige");
	}
}
//Used by PlayerDisplay 
int BoardDisplay::getRow()
{
	return _row;
}
//Used by PlayerDisplay
int BoardDisplay::getCol()
{
	return _col;
}