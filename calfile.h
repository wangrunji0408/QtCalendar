#ifndef CALFILE_H
#define CALFILE_H

#include "calitem.h"
#include <QFileInfo>
#include <QDate>

class CalFile: public CalItem
{
public:
	CalFile (QFileInfo fileInfo, QDate date);
private:
	QFileInfo	fileInfo;
	QDate		date;
};

#endif // CALFILE_H
