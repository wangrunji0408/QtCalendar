#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>
#include <QMouseEvent>

namespace Ui {
class DayWidget;
}

class DayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DayWidget(QWidget *parent = 0);
	~DayWidget();
	void setDate (const QDate& _date);

private:
	Ui::DayWidget *ui;
	QDate date;
};

#endif // DAYWIDGET_H
