#ifndef CALEVENT_H
#define CALEVENT_H

#include "calitem.h"
#include <QString>
#include <QTime>

class CalEvent: public CalItem
{
public:
	CalEvent(QString name, QString address, QTime tBegin, QTime tEnd, int priority = 0);
private:
	QString	name;
	QString	address;
	QTime	tBegin, tEnd;
	int		priority;
};

#endif // CALEVENT_H
