#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "calitemall.h"
#include "DayInfoWidget.h"
#include "CalManager.h"

namespace Ui {
class DayWidget;
}

class DayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DayWidget(ICalManager* _calManager, QWidget *parent = 0);
	~DayWidget();
	void setDate (const QDate& _date);
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
};

#endif // DAYWIDGET_H
