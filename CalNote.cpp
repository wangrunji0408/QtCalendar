#include "calnote.h"

CalNote::CalNote(const QString &note, const QDate &date):
	CalOneDayItem(date)
{
	this->note = note;
	this->date = date;
}
