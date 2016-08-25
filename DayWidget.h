#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDate>
#include <QMouseEvent>
#include "calitemall.h"
#include "DayInfoWidget.h"

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
	void setItemList (QVector<const CalItem*> const& _itemList);
	void mouseReleaseEvent(QMouseEvent* e) override;

private:
	Ui::DayWidget *ui;
	QDate date;
	QVector<const CalItem*> itemList;
};

#endif // DAYWIDGET_H
