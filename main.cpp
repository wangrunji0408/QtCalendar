#include "mainwindow.h"
#include "calender.h"
#include <QApplication>

#include "EventSettingDialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Calender cal;
	cal.show();

	EventSettingDialog dia;
	dia.show();
	dia.exec();
	auto event = dia.getEvent();
	EventSettingDialog dia1(event);
	dia1.show();

	return a.exec();
}
