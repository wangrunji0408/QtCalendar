#ifndef CALITEM_H
#define CALITEM_H

#include <QTime>
#include <QDate>
#include <QVector>

class CalItem
{
public:
	CalItem ();
	CalItem (QTime createTime);
	virtual bool inDate (QDate date) const = 0;
	virtual QVector<QDate> getDateList () const = 0;
protected:
	QTime createTime;
};

class CalOneDayItem: public CalItem
{
protected:
	QDate date;
public:
	CalOneDayItem (QDate date);
	QDate getDate () const;

	// CalItem interface
public:
	virtual bool inDate(QDate date) const override;
	virtual QVector<QDate> getDateList() const override;
};

#endif // CALITEM_H
