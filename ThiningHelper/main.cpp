#include "thininghelper.h"
#include <QtWidgets/QApplication>
#include <qtextcodec.h>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));

	QTextCodec *textCode = QTextCodec::codecForLocale();

	QApplication a(argc, argv);
	ThiningHelper w;
	w.show();
	return a.exec();
}
