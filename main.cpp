#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include "GUI/calender.h"
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Calender cal(&a);
	cal.show();

	return a.exec();
}
