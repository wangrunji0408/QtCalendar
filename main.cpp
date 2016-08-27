#include <QApplication>
#include <QDebug>
#include "GUI/calender.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Calender cal;
	cal.show();

	return a.exec();
}
