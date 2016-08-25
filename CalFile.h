#ifndef CALFILE_H
#define CALFILE_H

#include "CalItem.h"
#include <QFileInfo>
#include <QDate>

struct CalFile: public CalOneDayItem
{
	QString		filePath;
	CalFile () {type = File;}
};

#endif // CALFILE_H
