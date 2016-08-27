#ifndef CALFILE_H
#define CALFILE_H

#include "CalItem.h"
#include <QFileInfo>
#include <QDir>
#include <QDate>

struct CalFile: public CalOneDayItem
{
	QFileInfo		fileInfo;

	CalFile () {}
	CalFile (QString filePath, QDate _date);

	virtual CalItemType type () const override {return File;};
	bool copyTo(QDir dir);
	virtual QVariantMap toVariantMap () const override;
	virtual void fromVariantMap (QVariantMap const& v) override;
};

#endif // CALFILE_H
