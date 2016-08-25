#ifndef CALNOTE_H
#define CALNOTE_H

#include "calitem.h"

class CalNote: public CalOneDayItem
{
public:
	CalNote (const QString& note, const QDate& date);
private:
	QString note;
};

#endif // CALNOTE_H
