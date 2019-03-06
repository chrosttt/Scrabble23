#ifndef GRAPHICUSERINTERFACE_H
#define GRAPHICUSERINTERFACE_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QCloseEvent>
#include "UserInterface.h"
#include "ScrabbleGUI.h"
#include "PlayersWidget.h"

class GraphicUserInterface : public QWidget
{
  Q_OBJECT

    public:
    GraphicUserInterface (ScrabbleGUI* S);

    void closeEvent (QCloseEvent *event);

    public slots:
    void confirmPressed ();
    void quitPressed ();

 private:
    QPushButton *quitButton, *confirmButton;
    QSpinBox *number;
    UserInterface* UI;
    class PlayersWidget* PW;
    class ScrabbleGUI* _S;
};

#endif