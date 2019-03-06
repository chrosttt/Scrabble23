#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QAbstractButton>
#include <QFrame>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPaintEvent>
#include "UserInterface.h"
#include "ScrabbleGUI.h"

class GameWindow : public QWidget
{
  Q_OBJECT

    public:
    GameWindow (UserInterface* UI, ScrabbleGUI* S);

 private:
    UserInterface* _UI;
    ScrabbleGUI* _S;
    class ScoreDisplay* _SD;
    class PlayerDisplay* _PD;
    class BoardDisplay* _BD;
    QFrame* frame;
    QHBoxLayout* mainLayout;
    QVBoxLayout* playerLayout; 
};

#endif