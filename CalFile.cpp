#include "CalFile.h"
#include <QFile>
#include <QDebug>

CalFile::CalFile(QString filePath, QDate _date):
	fileInfo(filePath)
{
	date = _date;
}

bool CalFile::copyTo(QDir dir)
{
	if(!dir.exists())
		if(!dir.mkdir(dir.absolutePath()))
			return false;
	QString newPath = dir.absolutePath() + "/" + fileInfo.fileName();
	qDebug() << fileInfo.filePath() << " -> " << newPath;
	if(QFile::copy(fileInfo.filePath(), newPath))
	{
		fileInfo.setFile(newPath);
	}
	else
	{
		qDebug() << "Copy Error!";
	}
}
