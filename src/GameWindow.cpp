#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QAbstractButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPaintEvent>
#include "BoardDisplay.h"
#include "ScoreDisplay.h"
#include "PlayerDisplay.h"
#include "GameWindow.h"


//Creates main game window
GameWindow::GameWindow(UserInterface* UI, ScrabbleGUI* S)
{
	_UI = UI;
	_S = S;
	_SD = new ScoreDisplay(_UI);
	_BD = new BoardDisplay(_S->getBoard(), _UI);
	_PD = new PlayerDisplay(_UI, _S, _BD, _SD);
	mainLayout = new QHBoxLayout();
	playerLayout = new QVBoxLayout();
	mainLayout->addWidget(_BD);
	mainLayout->addLayout(playerLayout);
	playerLayout->addWidget(_SD);
	playerLayout->addWidget(_PD);
	setLayout(mainLayout);
	this->setWindowTitle("Scrabble-Qt");

}