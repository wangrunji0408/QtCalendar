#ifndef CALNOTE_H
#define CALNOTE_H

#include "CalItem.h"

class CalNote: public CalOneDayItem
{
public:
	QString note;

	CalNote () {}
	CalNote (const QString& note, const QDate& date);
	virtual CalItemType type () const override {return Note;};
	virtual QVariantMap toVariantMap () const override;
	virtual void fromVariantMap (QVariantMap const& v) override;
};

#endif // CALNOTE_H
