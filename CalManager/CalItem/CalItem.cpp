#include "CalItem.h"

bool CalOneDayItem::inDate(QDate date) const
{
	return date == this->date;
}

QVector<QDate> CalOneDayItem::getDateList() const
{
	return QVector<QDate>(1, date);
}
