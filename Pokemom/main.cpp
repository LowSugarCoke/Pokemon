#include "Pokemom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Pokemom w;
	w.show();
	return a.exec();
}
