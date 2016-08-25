#include "calevent.h"

CalEvent::CalEvent(QString name, QString address, QTime tBegin, QTime tEnd, int priority)
{
	this->name = name;
	this->address = address;
	this->tBegin = tBegin;
	this->tEnd = tEnd;
	this->priority = priority;
}
