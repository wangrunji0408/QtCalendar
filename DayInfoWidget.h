#ifndef DAYINFOWIDGET_H
#define DAYINFOWIDGET_H

#include <QWidget>
#include "calitemall.h"

namespace Ui {
class DayInfoWidget;
}

class DayInfoWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DayInfoWidget(const QDate& _date,
						   const QVector<const CalItem*> &itemList,
						   QWidget *parent = 0);
	~DayInfoWidget();
	void setItemList (const QVector<const CalItem*> &itemList);

private:
	Ui::DayInfoWidget *ui;
	QDate date;
};

#endif // DAYINFOWIDGET_H
