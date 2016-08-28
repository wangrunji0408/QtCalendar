#ifndef CALENDER_H
#define CALENDER_H

#include <QWidget>
#include <QLabel>
#include <QDragEnterEvent>
#include "DayWidget.h"
#include "../CalManager/CalManager.h"
#include "EventFilter/windowdrageventfilter.h"

namespace Ui {
class Calender;
}

class Calender : public QWidget
{
	Q_OBJECT

public:
	explicit Calender(QWidget *parent = 0);
	~Calender();

public:
	void nextMonth ();
	void lastMonth ();
	void goToday();

	void dragEnterEvent(QDragEnterEvent *event) override;

private slots:
	void on_goTodayButton_clicked();
	void on_goLeftButton_clicked();
	void on_goRightButton_clicked();
	void on_addItemButton_clicked();
	void on_settingButton_clicked();
	void on_fix_clicked(bool checked);

public slots:
	void showDayInfoWidget (QDate date);
	void update ();

private:
	QDate getFirstDayOfMonth ();
	void init ();

private:
	Ui::Calender *ui;
	int firstDayOfWeek;	// 1-7
	int year, month;
	DayWidget*	dayWidget[5][7];
	QLabel*		weekdayLabel[7];
	ICalManager* calManager;
	WindowDragEventFilter windowDrag;
};

#endif // CALENDER_H
