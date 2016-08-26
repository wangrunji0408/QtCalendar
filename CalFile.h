#ifndef CALFILE_H
#define CALFILE_H

#include "CalItem.h"
#include <QFileInfo>
#include <QDir>
#include <QDate>

struct CalFile: public CalOneDayItem
{
	QFileInfo		fileInfo;

	CalFile (QString filePath, QDate _date);
	virtual CalItemType type () const override {return File;};
	bool copyTo(QDir dir);
};

#endif // CALFILE_H
