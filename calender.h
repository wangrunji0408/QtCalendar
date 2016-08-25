#ifndef CALENDER_H
#define CALENDER_H

#include <QWidget>
#include <QLabel>
#include <DayWidget.h>
#include <CalManager.h>

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

private slots:
	void on_goTodayButton_clicked();
	void on_goLeftButton_clicked();
	void on_goRightButton_clicked();
	void on_addItemButton_clicked();

private:
	QDate getFirstDayOfMonth ();
	void init ();
	void update ();		// 根据 yearAndMonth 更新 dayWidget[][]


private:
	Ui::Calender *ui;
	int firstDayOfWeek;	// 1-7
	int year, month;
	DayWidget*	dayWidget[5][7];
	QLabel*		weekdayLabel[7];
	ICalManager* calManager;
};

#endif // CALENDER_H
