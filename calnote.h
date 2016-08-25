#ifndef CALNOTE_H
#define CALNOTE_H

#include "calitem.h"

class CalNote: public CalItem
{
public:
	CalNote (const QString& note);
private:
	QString note;
};

#endif // CALNOTE_H
