#include "CalFile.h"
#include <QFile>

CalFile::CalFile(QString filePath, QDate _date):
	fileInfo(filePath)
{
	date = _date;
}

bool CalFile::copyTo(QDir dir)
{
	if(!dir.exists())
		if(!dir.mkpath(dir.absolutePath()))
			return false;
	QString newPath = dir.absolutePath() + "/" + fileInfo.fileName();
	qDebug() << fileInfo.filePath() << " -> " << newPath;
	if(QFile::copy(fileInfo.filePath(), newPath))
	{
		fileInfo.setFile(newPath);
		return true;
	}
	else
	{
		qDebug() << "Copy Error!";
	}
	return false;
}

QVariantMap CalFile::toVariantMap() const
{
	QVariantMap v;
	v.insert("type", "File");
	v.insert("createTime", createTime);
	v.insert("color", color);
	v.insert("date", date);
	v.insert("filePath", fileInfo.filePath());
	return v;
}

void CalFile::fromVariantMap(const QVariantMap &v)
{
	createTime = v["createTime"].toDateTime();
	color = v["color"].value<QColor>();
	date = v["date"].toDate();
	fileInfo = (QFileInfo) v["filePath"].toString();
}
