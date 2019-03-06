#ifndef PLAYERDISPLAY_H
#define PLAYERDISPLAY_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <vector>
#include <QLabel>
#include <QAbstractButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPaintEvent>
#include "UserInterface.h"
#include "ScrabbleGUI.h"
#include "BoardDisplay.h"
#include "ScoreDisplay.h"

class PlayerDisplay : public QWidget
{
  Q_OBJECT

    public:
    PlayerDisplay (UserInterface* UI, ScrabbleGUI* S, BoardDisplay* boardDisp, ScoreDisplay* scoreDisp);
    void makeTiles();
    void updateTiles();
    bool onFirstTile(int row, int col, char dir, std::string word, Board* board);
    void endGame();

    public slots:
    void passPressed();
    void exchangePressed();
    void placePressed();
    void helpPressed();

 private:
    UserInterface* _UI;
    bool firstMove;
    ScrabbleGUI* _S;
    BoardDisplay* _boardDisp;
    ScoreDisplay* _scoreDisp;
    Board* board;
    Bag* bag;
    Dictionary* dict;
    std::vector<char> drawnTiles;
    QVBoxLayout* mainLayout;
    QMessageBox* msgBox;
    QHBoxLayout* tilesLayout; 
    QHBoxLayout* buttonsLayout;
    QButtonGroup* moveDirection;
    QHBoxLayout* radioLayout;
    QRadioButton* horizMove;
    QRadioButton* vertMove;
    QPushButton* helpButton;
    QLineEdit* moveField;
    QLabel* nameLabel;
    QPushButton* passButton; 
    QPushButton* exchangeButton;
    QPushButton* placeButton;
    QLabel* tile;
    std::vector<QLabel*> tileList;
    int passCounter;
};

#endif