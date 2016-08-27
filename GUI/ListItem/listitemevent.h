#ifndef LISTITEMEVENT_H
#define LISTITEMEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include "../../CalManager/CalManager.h"

namespace Ui {
class ListItemEvent;
}

class ListItemEvent : public QWidget
{
	Q_OBJECT

public:
	explicit ListItemEvent(const CalEvent* _event, QDate _date, ICalManager* _calManager, QWidget *parent = 0);
	~ListItemEvent();

public:
	void keyPressEvent(QKeyEvent* ke) override;
	void mouseDoubleClickEvent(QMouseEvent *) override;

private:
	Ui::ListItemEvent *ui;
	const CalEvent* event;
	ICalManager* calManager;
	QDate date;
};

#endif // LISTITEMEVENT_H
