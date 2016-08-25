#ifndef CALFILE_H
#define CALFILE_H

#include "calitem.h"
#include <QFileInfo>
#include <QDate>

class CalFile: public CalOneDayItem
{
public:
	CalFile (QString filePath, QDate date);
private:
	QString		filePath;
};

#endif // CALFILE_H
