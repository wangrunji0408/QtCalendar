#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "DayInfoWidget.h"
#include "../CalManager/CalManager.h"

namespace Ui {
class DayWidget;
}

class DayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DayWidget(ICalManager* _calManager, QWidget *parent = 0);
	~DayWidget();
	void setDate (const QDate& _date, bool _inMonth);
	void update ();
	void mouseReleaseEvent(QMouseEvent* e) override;
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;

signals:
	void showDayInfoWidget (QDate);

private:
	Ui::DayWidget *ui;
	QDate date;
	QVector<const CalItem*> itemList;
	ICalManager* calManager;
	bool inMonth;
};

#endif // DAYWIDGET_H
