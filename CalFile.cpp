#include "calfile.h"

CalFile::CalFile (QString filePath, QDate date):
	CalOneDayItem(date)
{
	this->filePath = filePath;
	this->date = date;
}
