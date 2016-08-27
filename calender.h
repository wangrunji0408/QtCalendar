#ifndef CALENDER_H
#define CALENDER_H

#include <QWidget>
#include <QLabel>
#include <DayWidget.h>
#include <CalManager.h>
#include <QDragEnterEvent>
#include "windowdrag.h"

namespace Ui {
class Calender;
}

class Calender : public QWidget
{
	Q_OBJECT
	WINDOW_DRAG

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
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

public slots:
	void showDayInfoWidget (QDate date);

private:
	QDate getFirstDayOfMonth ();
	void init ();

public slots:
	void update ();

private:
	Ui::Calender *ui;
	int firstDayOfWeek;	// 1-7
	int year, month;
	DayWidget*	dayWidget[5][7];
	QLabel*		weekdayLabel[7];
	ICalManager* calManager;
};

#endif // CALENDER_H
