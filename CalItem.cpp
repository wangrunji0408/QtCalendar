#include "calitem.h"

CalItem::CalItem()
{
	createTime = QTime::currentTime();
}

CalOneDayItem::CalOneDayItem(QDate date)
{
	this->date = date;
}

bool CalOneDayItem::inDate(QDate date) const
{
	return date == this->date;
}

QVector<QDate> CalOneDayItem::getDateList() const
{
	return QVector<QDate>(1, date);
}
