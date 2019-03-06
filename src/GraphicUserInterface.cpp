#include "GraphicUserInterface.h"
#include "UserInterface.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <iostream>

GraphicUserInterface::GraphicUserInterface (ScrabbleGUI* S)
{

  _S = S;
  PW = new PlayersWidget(_S);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget (new QLabel ("Welcome to Ashish's Awesome Scrabble!"));

  number = new QSpinBox;
  number->setMinimum (1); number->setMaximum(8); 
  number->setValue(2); number->setSingleStep(1);
  QFormLayout *fl = new QFormLayout;
  fl->addRow ("Num&ber of Players:", number);
  mainLayout->addLayout (fl);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  quitButton = new QPushButton ("&Quit");
  confirmButton = new QPushButton ("&Confirm");
  buttonLayout->addWidget (confirmButton);
  buttonLayout->addWidget (quitButton);

  connect (confirmButton, SIGNAL(clicked()), this, SLOT(confirmPressed()));
  connect (quitButton, SIGNAL(clicked()), this, SLOT(quitPressed()));

  mainLayout->addLayout (buttonLayout);
  setLayout (mainLayout);
  this->setWindowTitle("Scrabble-Qt");
  
}

void GraphicUserInterface::closeEvent (QCloseEvent *event)
{
  QWidget::closeEvent (event);
}

void GraphicUserInterface::confirmPressed ()
{
  int numPlayers = number->value();
  PW->addPlayers(numPlayers, _S->getHandSize());
  PW->show();
  close();
}

void GraphicUserInterface::quitPressed ()
{
  close ();
}