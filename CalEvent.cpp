#include "calevent.h"

CalEvent::CalEvent(QString name, QString address, QDateTime tBegin, QDateTime tEnd, int priority)
{
	this->name = name;
	this->address = address;
	this->tBegin = tBegin;
	this->tEnd = tEnd;
	this->priority = priority;
}

bool CalEvent::inDate(QDate date) const
{
	return tBegin.date() <= date && tEnd.date() >= date;
}


QVector<QDate> CalEvent::getDateList() const
{
	QVector<QDate> dateList;
	for(QDate date = tBegin.date(); date <= tEnd.date(); date = date.addDays(1))
		dateList.append(date);
	return dateList;
}
