#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <vector>
#include <QAbstractButton>
#include <QGridLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay(UserInterface* UI)
{
	_UI = UI;
	mainLayout = new QVBoxLayout();
	scoresLayout = new QVBoxLayout();
	turnLabel = new QLabel();
	scoreLabel = new QLabel("SCORE:");
	turnLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	turnLabel->setLineWidth(1);
	turnLabel->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(turnLabel);
	mainLayout->addLayout(scoresLayout);
	scoreLabel->setAlignment(Qt::AlignCenter);
	scoresLayout->addWidget(scoreLabel);
	makeScore();
	setLayout(mainLayout);
}
//create the scoreboard
void ScoreDisplay::makeScore()
{
	std::string temp;
	std::string name = _UI->players[_UI->getTurn()]->getName();
	temp = "It is " + name + "'s turn!";
	turnLabel->setText(QString::fromStdString(temp));
	QString msg;
	for(unsigned int i = 0; i < _UI->players.size(); i++){
		msg = QString::fromStdString(_UI->players[i]->getName());
		msg += ": ";
		msg += QString::number(_UI->players[i]->getScore());
		playerScore = new QLabel(msg);
		scoreList.push_back(playerScore);
		scoresLayout->addWidget(playerScore);
	}
}
//update the scoreboard with vector of pointers to QLabels
void ScoreDisplay::updateScore()
{
	std::string name = _UI->players[_UI->getTurn()]->getName();
	std::string temp = "It is " + name + "'s turn!";
	turnLabel->setText(QString::fromStdString(temp));
	QString msg;
	for(unsigned int i = 0; i < _UI->players.size(); i++){
		msg = QString::fromStdString(_UI->players[i]->getName());
		msg += " ";
		msg += QString::number(_UI->players[i]->getScore());
		scoreList[i]->setText(msg);
	}
}