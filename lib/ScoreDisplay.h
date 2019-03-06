#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QFrame>
#include <QLabel>
#include <QAbstractButton>
#include <QGridLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include "Board.h"
#include "UserInterface.h"

class ScoreDisplay : public QWidget
{
  Q_OBJECT

    public:
    ScoreDisplay (UserInterface* UI);
    void makeScore();
    void updateScore();

 private:
    QVBoxLayout* mainLayout;
    QVBoxLayout* scoresLayout;
    QVBoxLayout* turnLayout;
    QLabel* scoreLabel;
    QFrame* frame;
    QLabel* turnLabel;
    QLabel* playerScore;
    UserInterface* _UI;
    std::vector<QLabel*> scoreList;
};

#endif