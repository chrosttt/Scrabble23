#ifndef PLAYERSWIDGET_H
#define PLAYERSWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <vector>
#include "UserInterface.h"
#include "ScrabbleGUI.h"

class PlayersWidget : public QWidget {
	Q_OBJECT

	public:
		PlayersWidget(ScrabbleGUI* S);
		//void closeEvent (QCloseEvent *event);
		void addPlayers(int numPlayers, int handSize);

    public slots:
    	void confirmPressed ();
    	//void quitPressed ();

	private:
		QVBoxLayout* layout;
		QLabel* message;
		QGridLayout* playerLayout;
		QPushButton* confirmButton;
		QWidget* playersContainerWidget;
		UserInterface* UI;
		std::vector<QLineEdit*> names;
		std::vector<std::string> playerNames;
		int _numPlayers;
		int _handSize;
		class ScrabbleGUI* _S;
		class GameWindow* _G;
		class BoardDisplay* _board;
		class PlayerDisplay* _player;
		

		
};
#endif
