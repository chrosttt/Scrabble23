#include <QApplication>
#include "GraphicUserInterface.h"
#include "BoardDisplay.h"

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);
  ScrabbleGUI* s = new ScrabbleGUI(argv[1]);
  GraphicUserInterface* GUI = new GraphicUserInterface(s);
  GUI->show();
  return app.exec ();
}
