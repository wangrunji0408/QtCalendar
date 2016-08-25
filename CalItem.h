#ifndef CALITEM_H
#define CALITEM_H

#include <QTime>
#include <QDate>
#include <QVector>
#include <QColor>

struct CalItem
{
public:
	QDateTime	createTime	= QDateTime::currentDateTime();
	QColor		color		= Qt::red;
public:
	virtual bool inDate (QDate date) const = 0;
	virtual QVector<QDate> getDateList () const = 0;
};

struct CalOneDayItem: public CalItem
{
public:
	QDate date;

	// CalItem interface
public:
	virtual bool inDate(QDate date) const override;
	virtual QVector<QDate> getDateList() const override;
};

#endif // CALITEM_H
