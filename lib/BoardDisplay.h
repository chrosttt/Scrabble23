#ifndef BOARDDISPLAY_H
#define BOARDDISPLAY_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QAbstractButton>
#include <QGridLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include "Board.h"
#include "UserInterface.h"

class BoardDisplay : public QWidget
{
  Q_OBJECT

    public:
    BoardDisplay (Board* board, UserInterface* UI);
    void updateBoard();
    void resetSquare(QAbstractButton* button);
    int getCol();
    int getRow();

    //void closeEvent (QCloseEvent *event);

    public slots:
    void confirmPressed(QAbstractButton* button);

 private:
    QGridLayout* boardLayout;
    UserInterface* _UI;
    Board* _board;
    QPushButton* square;
    QLabel* placedTile;
    QAbstractButton* tempButton;
    QButtonGroup* allTiles;
    int counter;
    int _row, _col;
};

#endif