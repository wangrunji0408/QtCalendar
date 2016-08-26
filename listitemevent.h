#ifndef LISTITEMEVENT_H
#define LISTITEMEVENT_H

#include <QWidget>
#include <QKeyEvent>
//#include <QMouseEvent>
#include "calevent.h"
#include "CalManager.h"

namespace Ui {
class ListItemEvent;
}

class ListItemEvent : public QWidget
{
	Q_OBJECT

public:
	explicit ListItemEvent(const CalEvent* _event, QDate _date, ICalManager* _calManager, QWidget *parent = 0);
	~ListItemEvent();
	const CalEvent* event;
	void keyPressEvent(QKeyEvent* ke) override;
	void mouseDoubleClickEvent(QMouseEvent *) override;

private:
	Ui::ListItemEvent *ui;
	ICalManager* calManager;
	QDate date;
};

#endif // LISTITEMEVENT_H
