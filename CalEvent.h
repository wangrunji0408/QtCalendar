#ifndef CALEVENT_H
#define CALEVENT_H

#include "CalItem.h"
#include <QString>
#include <QTime>

class CalEvent: public CalItem
{
public:
	CalEvent(QString name, QString address, QDateTime tBegin, QDateTime tEnd, int priority = 0);
private:
	QString		name;
	QString		address;
	QDateTime	tBegin, tEnd;
	int			priority;

	// CalItem interface
public:
	virtual bool inDate (QDate date) const override;
	virtual QVector<QDate> getDateList() const override;
};

#endif // CALEVENT_H
