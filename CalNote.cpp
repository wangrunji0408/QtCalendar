#include "CalNote.h"

CalNote::CalNote(const QString &note, const QDate &date)
{
	this->note = note;
	this->date = date;
}

QVariantMap CalNote::toVariantMap() const
{
	QVariantMap v;
	v.insert("type", "Note");
	v.insert("createTime", createTime);
	v.insert("color", color);
	v.insert("date", date);
	v.insert("note", note);
	return v;
}

void CalNote::fromVariantMap(const QVariantMap &v)
{
	createTime = v["createTime"].toDateTime();
	color = v["color"].value<QColor>();
	date = v["date"].toDate();
	note = v["note"].toString();
}
