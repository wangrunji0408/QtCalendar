#include "mainwindow.h"
#include "calender.h"
#include <QApplication>

#include "EventSettingDialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Calender cal;
	cal.show();

	return a.exec();
}
