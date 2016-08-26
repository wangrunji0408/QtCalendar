#ifndef CALNOTE_H
#define CALNOTE_H

#include "CalItem.h"

class CalNote: public CalOneDayItem
{
public:
	CalNote (const QString& note, const QDate& date);
	virtual CalItemType type () const override {return Note;};
private:
	QString note;
};

#endif // CALNOTE_H
