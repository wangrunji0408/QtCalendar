#ifndef CALEVENT_H
#define CALEVENT_H

#include "CalItem.h"
#include <QString>
#include <QTime>
#include <QSet>
#include <QVariant>

class CalEvent: public CalItem
{
public:
	enum RepeatCycle {None = 0, Day = 1, Week = 2, Month = 3, Year = 4};
	QString		name;
	QString		address;
	QDateTime	tBegin, tEnd;
	QString		note;
	int			priority = 0;
	// Repeat
	RepeatCycle	repeatCycle = None;
	int			repeatTimes = 1;	// -1: +oo
	QSet<int>	deletedRepeatIndex;

	static const int PRIORITY_MAX = 3;

	// CalItem interface
public:
	virtual CalItemType type () const override {return Event;};
	virtual bool inDate (QDate date) const override;
	virtual QVector<QDate> getDateList() const override;
//	virtual QJsonObject toJson () const override;
//	virtual void fromJson (QJsonObject const& json) override;
	virtual QVariantMap toVariantMap () const override;
	virtual void fromVariantMap (QVariantMap const& v) override;

	bool crossDate () const;
	int getRepeatIndex (QDate date) const;
	void delRepeatIndex (int index);
	void delRepeatIndexAfter (int index);
	int error () const;

private:
	void nextDate (QDateTime &t1, QDateTime &t2) const;
};

//Q_DECLARE_METATYPE(CalEvent)

#endif // CALEVENT_H
