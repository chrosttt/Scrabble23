#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <iostream>
#include <sstream>
#include <string>
#include <QString>
#include <vector>
#include "PlayersWidget.h"
#include "BoardDisplay.h"
#include "PlayerDisplay.h"
#include "GameWindow.h"

PlayersWidget::PlayersWidget(ScrabbleGUI* S)
{
  	_S = S;
  	UI = new UserInterface();
	layout = new QVBoxLayout();
	message = new QLabel("Please enter the name of each player.");
	layout->addWidget(message);
	playerLayout = new QGridLayout();
	playersContainerWidget = new QWidget();
	playersContainerWidget->setLayout(playerLayout);
	layout->addWidget(playersContainerWidget);
	confirmButton = new QPushButton("Confirm");
	layout->addWidget(confirmButton);
	setLayout(layout);
	this->setWindowTitle("Scrabble-Qt");

	connect (confirmButton, SIGNAL(clicked()), this, SLOT(confirmPressed()));
}
//Get player names
void PlayersWidget::addPlayers(int numPlayers, int handSize)
{
	_numPlayers = numPlayers;
	_handSize = handSize;
	QString msg;

	for(int i = 1; i < numPlayers+1; i++){
		msg = "";
		msg += "Player ";
		msg += QString::number(i);
		QLabel* playerLabel = new QLabel(msg);
		playerLayout->addWidget(playerLabel,i-1, 0, 1, 1);
		QLineEdit *name = new QLineEdit();
		playerLayout->addWidget(name, i-1, 1, 1, 1);
		names.push_back(name);
	}
}
//Create players in backend and open game window on button press
void PlayersWidget::confirmPressed()
{
	std::string temp;
	std::stringstream ss;
	for(int i = 0; i < _numPlayers; i++){
		temp = names[i]->text().toStdString();
		if(temp == ""){
			ss.str("");
			ss << (i+1);
			temp = "Player";
			temp += ss.str();
		}
		playerNames.push_back(temp);
	}
	UI->createNewPlayers(_numPlayers, _handSize, playerNames, _S->getBag());
	_G = new GameWindow(UI, _S);
	_G->show();
	close();
}