#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <iostream>
#include <string>
#include <sstream>
#include <QLabel>
#include <QAbstractButton>
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QFrame>
#include <QRectF>
#include <QPainter>
#include "PlayerDisplay.h"
//Constructor, gets points to all necessary classes in order to make moves
PlayerDisplay::PlayerDisplay(UserInterface* UI, ScrabbleGUI* S, BoardDisplay* boardDisp, ScoreDisplay* scoreDisp)
{
	passCounter = 0;
	_UI = UI;
	_S = S;
	msgBox = new QMessageBox();
	firstMove = true;
	_boardDisp = boardDisp;
	_scoreDisp = scoreDisp;
	board = S->getBoard();
	bag = S->getBag();
	dict = S->getDict();
	mainLayout = new QVBoxLayout();
	tilesLayout = new QHBoxLayout();
	moveField = new QLineEdit();
	nameLabel = new QLabel();

	buttonsLayout = new QHBoxLayout();
	passButton = new QPushButton("PASS");
	exchangeButton = new QPushButton("EXCHANGE");
	placeButton = new QPushButton("PLACE");
	buttonsLayout->addWidget(placeButton);
	buttonsLayout->addWidget(exchangeButton);
	buttonsLayout->addWidget(passButton);
	mainLayout->addLayout(tilesLayout);

	mainLayout->addWidget(moveField);
	mainLayout->addLayout(buttonsLayout);

	radioLayout = new QHBoxLayout();
	moveDirection = new QButtonGroup();
	horizMove = new QRadioButton("---");
	horizMove->setChecked(true);
	vertMove = new QRadioButton("|");
	helpButton = new QPushButton();
	helpButton->setText("How to Play");
	moveDirection->addButton(horizMove);
	moveDirection->addButton(vertMove);
	radioLayout->addWidget(horizMove);
	radioLayout->addWidget(vertMove);
	radioLayout->addWidget(helpButton);
	mainLayout->addLayout(radioLayout);
	

	makeTiles();
	setLayout(mainLayout);
	connect (passButton, SIGNAL(clicked()), this, SLOT(passPressed()));
	connect (exchangeButton, SIGNAL(clicked()), this, SLOT(exchangePressed()));
	connect (placeButton, SIGNAL(clicked()), this, SLOT(placePressed()));
	connect (helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()));
}

//Make the tile display
void PlayerDisplay::makeTiles()
{
	std::string tileLetter;
	QString msg;
	int numTiles = _UI->players[_UI->getTurn()]->_playerTiles.size();
	for(int i = 0; i < numTiles; i++){
		tileLetter = _UI->players[_UI->getTurn()]->_playerTiles[i]->getLetter();
		msg = QString::fromStdString(tileLetter);
		msg += QString::number(_UI->players[_UI->getTurn()]->_playerTiles[i]->getPoints());
		tile = new QLabel(msg);
		tileList.push_back(tile);
		tile->setFrameStyle(QFrame::Panel | QFrame::Raised);
		tile->setLineWidth(4);
		tile->setStyleSheet("background-color: khaki;");
		tile->setAlignment(Qt::AlignCenter);
		tile->setFixedSize(50,50);
		tilesLayout->addWidget(tile);
	}
}
//Update the letter on each tile using vector of pointers to QLabel
void PlayerDisplay::updateTiles()
{
	std::string tileLetter;
	QString msg;
	int size;
	int numTiles = _UI->players[_UI->getTurn()]->_playerTiles.size();
	for(int i = 0; i < numTiles; i++){
		tileLetter = _UI->players[_UI->getTurn()]->_playerTiles[i]->getLetter();
		msg = QString::fromStdString(tileLetter);
		msg += QString::number(_UI->players[_UI->getTurn()]->_playerTiles[i]->getPoints());
		tileList[i]->setText(msg);
	}
	//If a player has less than default number of tiles, hide extra tiles
	if(numTiles < (int)tileList.size()){
		size = tileList.size()-numTiles;
		for(int i = 0; i < size; i++){
			tileList[tileList.size()-1-i]->setVisible(false);
		}
	}
}

void PlayerDisplay::helpPressed()
{
	msgBox->setWindowTitle("Help");
	msgBox->setText("Select a square to start your move by clicking directly on the board.\
	The square will turn yellow indicating that it has been selected.\
	Select a horizontal placement by clicking the '---' button and a vertical placement by clicking the '|' button.\
	\n\nIn order to select tiles, simply type in the tiles you would like to use \
	in the order you would like them placed. For '?' tiles, type the letter you would like to use it as directly following it. \
	For example, typing 'CA?R', indicates that you are using your blank tile as the letter R. ");
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->exec();
}

//Handles what happens when pass is pressed
void PlayerDisplay::passPressed()
{
	passCounter++;
	if(passCounter == (int)_UI->players.size()){
		endGame();
		return;
	}
	_UI->switchTurns();
	std::string temp;
	temp += "You passed your turn!\n";
	temp += "It is now ";
	temp += _UI->players[_UI->getTurn()]->getName();
	temp += "'s turn!";
	msgBox->setWindowTitle("Pass");
	msgBox->setText(QString::fromStdString(temp));
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->exec();
	moveField->setText("");
	_scoreDisp->updateScore();
	updateTiles();
	return;
}
//Handles what happens when exchange is pressed
void PlayerDisplay::exchangePressed()
{
	passCounter = 0;
	if(moveField->text().isEmpty()){
		msgBox->setWindowTitle("Error");
		msgBox->setText("Please enter a tile to exchange!");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	int pos = -1;
	bool hasTile = true;
	std::string word = moveField->text().toStdString();
	for(unsigned int i = 0; i < word.length(); i++){
		word[i] = toupper(word[i]);
	}
	for(unsigned int i = 0; i < word.length(); i++){
		if(!_UI->players[_UI->getTurn()]->findTile(word[i],pos)){
			msgBox->setWindowTitle("Error");
			msgBox->setText("You do not have this tile. Please try again!");
			msgBox->setStandardButtons(QMessageBox::Ok);
			msgBox->exec();
			moveField->setText("");
			hasTile = false;
			return;
		}
	}
	if(hasTile){
		_UI->players[_UI->getTurn()]->executeExchangeMove(*(_S->getBag()), word, drawnTiles);
		std::string text;
		for(unsigned int i = 0; i < drawnTiles.size(); i++){
			text += drawnTiles[i];
			text += " ";
		}
		msgBox->setWindowTitle("Exchange");
		std::string temp = "You exchanged tiles: ";
		temp += word;
		temp += "\n";
		temp += " You received tiles: ";
		temp += text;
		msgBox->setText(QString::fromStdString(temp));
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		moveField->setText("");
		_UI->switchTurns();
		_scoreDisp->updateScore();
		updateTiles();

	}
}
//Handles what happens when place is pressed
void PlayerDisplay::placePressed()
{
	passCounter = 0;
	if(moveField->text().isEmpty()){
		msgBox->setWindowTitle("Error");
		msgBox->setText("Please enter a tile to place!");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	//check if a square has been selected
	int r = _boardDisp->getRow();
	int c = _boardDisp->getCol();
	int pos = -1;
	if(r == -1){
		msgBox->setWindowTitle("Error");
		msgBox->setText("Please select a square to place the tile on!");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	int numBlanks = 0;
	bool isValid = false;
	bool isAdj = true;
	bool hasTile = true;
	QAbstractButton* button = moveDirection->checkedButton();
	QString msg = button->text();
	std::string temp  = msg.toStdString();
	char dir = temp[0];
	std::string word = moveField->text().toStdString();
	//handles blank tile case
	for(unsigned int i = 0; i < word.length(); i++){
		if(word[i] == '?')
			numBlanks++;
		else
			word[i] = toupper(word[i]);
		}
	//check if a tile would go out of bounds
	if((dir == '-' && (c - numBlanks + (int)word.length() > board->getColSize())) ||
	(dir == '|' && (r - numBlanks + (int)word.length() > board->getRowSize()))) {
		msgBox->setWindowTitle("Error");
		msgBox->setText("One or more of your tiles would end up out of bounds. \n Please try another move.");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	//first move must be on starting square
	if(firstMove && !onFirstTile(r,c,dir,word,board)){
		msgBox->setWindowTitle("Error");
		msgBox->setText("First move must start on the starting square. \
			\n Please try another move.");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	//Check if user has the tiles they selected to place
	for(unsigned int i = 0; i < word.length(); i++){
		if(i != 0 && word[i-1] == '?'){
			continue;
		}
		if(!_UI->players[_UI->getTurn()]->findTile(word[i], pos)){
			msgBox->setWindowTitle("Error");
			msgBox->setText("You do not have this tile. \
			\n Please try another move.");
			msgBox->setStandardButtons(QMessageBox::Ok);
			msgBox->exec();
			moveField->setText("");
			hasTile = false;
			return;
		}
	}
	if(hasTile){
		isValid = _UI->players[_UI->getTurn()]->executePlaceMove(*bag,*dict,*board,dir,r+1,c+1,word,isAdj);
	}
	//check for adjacency in placed tiles
	if(!isValid && !isAdj){
		msgBox->setWindowTitle("Error");
		msgBox->setText("At least one tile must be adjacent to other tiles on the board. \
			Please try another move.");
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		return;
	}
	//case if a word created is not valid
	if(!isValid){
		std::string temp = "";
		temp += word;
		msgBox->setWindowTitle("Error");
		temp += " is invalid. Please try again.";
		msgBox->setText(QString::fromStdString(temp));
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		moveField->setText("");
		return;
	}	
	//Place tiles and get points + new tiles if valid
	if(isValid){
		firstMove = false;
		_boardDisp->updateBoard();
		std::string temp = "You placed: " + word + "\n";
		temp += "Words formed: ";
		std::vector<std::string> words = _UI->players[_UI->getTurn()]->getWordsFormed();
		for(unsigned int i = 0; i < words.size(); i++){
			temp += words[i];
			temp += " ";
		}
		temp += "\n";
		temp += "You scored: ";
		temp += _UI->players[_UI->getTurn()]->getMoveScore();
		temp += " points!";
		msgBox->setWindowTitle("Place");
		msgBox->setText(QString::fromStdString(temp));
		msgBox->setStandardButtons(QMessageBox::Ok);
		msgBox->exec();
		moveField->setText("");
		if(bag->tilesRemaining() == 0 && _UI->players[_UI->getTurn()]->getHandSize() == 0){
			endGame();
		}
		_UI->switchTurns();
		_scoreDisp->updateScore();
		updateTiles();
	}
}
//Checks if the first move is on the starting square
bool PlayerDisplay::onFirstTile(int row, int col, char dir, std::string word, Board* board)
{
	for(int i = 0; i < (int)word.length(); i++){
		if(dir == '|'){
			if(row + i == board->getStartY() && col == board->getStartX())
				return true;
		}
		else if (dir == '-'){
			if(col + i == board->getStartX() && row == board->getStartY())
				return true;
		}
	}
	return false;
}
//Create message box that shows winners, final score, score adjustments
void PlayerDisplay::endGame()
{
	std::vector<std::string> winners = _UI->endGame();
	std::stringstream ss;
	std::string temp = "Game Over!\n";
	int scoreChange = 0;
	if(_UI->players[_UI->getTurn()]->getHandSize() == 0){
		temp += "\n";
		temp += "Score Adjustments:\n\n";
		for(unsigned int i = 0; i < _UI->players.size(); i++){
			if((int)i == _UI->getTurn()){
				continue;
			}
			ss.str("");
			ss << _UI->players[i]->getHandScore();
			scoreChange += _UI->players[i]->getHandScore();
			temp += _UI->players[i]->getName();
			temp += " -";
			temp += ss.str();
			temp += " points";
			temp += "\n";
		}
		ss.str("");
		ss << scoreChange;
		temp += _UI->players[_UI->getTurn()]->getName();
		temp += " +";
		temp += ss.str();
		temp += " points";
		temp += "\n";
	}

	temp += "\nFinal Score:\n\n";
	for(unsigned int i = 0; i < _UI->players.size(); i++){
		ss.str("");
		ss << _UI->players[i]->getScore();
		temp += _UI->players[i]->getName();
		temp += ": ";
		temp += ss.str();
		temp += " points";
		temp += "\n";
	}
	temp += "\n";
	temp += "The winner(s) is(are): ";
	for(unsigned int i = 0; i < winners.size(); i++){
		if(i == winners.size()-1){
			temp += winners[i];
		}
		else{
			temp += winners[i];
			temp += ", ";
		}
	}
	msgBox->setWindowTitle("Game Over");
	msgBox->setText(QString::fromStdString(temp));
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->exec();
	qApp->quit();
} 