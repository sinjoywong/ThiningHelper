#include "thininghelper.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ThiningHelper w;
	w.show();
	return a.exec();
}
