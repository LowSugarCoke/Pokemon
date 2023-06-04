#include "Pokemon.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Pokemon w;
	w.show();
	return a.exec();
}
