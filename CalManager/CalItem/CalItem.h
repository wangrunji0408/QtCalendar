#ifndef CALITEM_H
#define CALITEM_H

#include <QTime>
#include <QDate>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>

struct CalItem
{
public:
	enum CalItemType
	{
		Item = 0, Event = 1, File = 2, Note = 3
	};

	QDateTime	createTime	= QDateTime::currentDateTime();
	QColor		color		= Qt::red;
public:
	virtual bool inDate (QDate date) const = 0;
	virtual QVector<QDate> getDateList () const = 0;
	virtual CalItemType type () const = 0;
	virtual QVariantMap toVariantMap () const = 0;
	virtual void fromVariantMap (QVariantMap const& v) = 0;
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
