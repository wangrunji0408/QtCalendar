#include "CalEvent.h"

bool CalEvent::inDate(QDate date) const
{
//	QDateTime t1 = tBegin, t2 = tEnd;
//	for(int i=0; i<repeatTimes; ++i)
//	{
//		if(!deletedRepeatIndex.contains(i)
//			&& t1.date() <= date && t2.date() >= date)
//			return true;
//		nextDate(t1, t2);
//	}
//	return false;
	return getRepeatIndex(date) != -1;
}

QVector<QDate> CalEvent::getDateList() const
{
	QVector<QDate> dateList;
	QDateTime t1 = tBegin, t2 = tEnd;
	for(int i=0; i<repeatTimes; ++i)
	{
		if(!deletedRepeatIndex.contains(i))
			for(QDate date = t1.date(); date <= t2.date(); date = date.addDays(1))
				dateList.append(date);
		nextDate(t1, t2);
	}
	return dateList;
}

QVariantMap CalEvent::toVariantMap() const
{
	QVariantMap v;
	v.insert("type", "Event");
	v.insert("createTime", createTime);
	v.insert("color", color);
	v.insert("name", name);
	v.insert("address", address);
	v.insert("tBegin", tBegin);
	v.insert("tEnd", tEnd);
	v.insert("note", note);
	v.insert("priority", priority);
	v.insert("repeatCycle", repeatCycle);
	v.insert("repeatTimes", repeatTimes);
	QVariantList list;
	for(int index: deletedRepeatIndex)
		list.append(index);
	v.insert("deletedRepeatIndex", list);
	return v;
}

void CalEvent::fromVariantMap(QVariantMap const& v)
{
	createTime = v["createTime"].toDateTime();
	color = v["color"].value<QColor>();
	name = v["name"].toString();
	address = v["address"].toString();
	tBegin = v["tBegin"].toDateTime();
	tEnd = v["tEnd"].toDateTime();
	note = v["note"].toString();
	priority = v["priority"].toInt();
	repeatCycle = (RepeatCycle)v["repeatCycle"].toInt();
	repeatTimes = v["repeatTimes"].toInt();
	deletedRepeatIndex.clear();
	for(auto var: v["deletedRepeatIndex"].toList())
		deletedRepeatIndex.insert(var.toInt());
}

//QJsonObject CalEvent::toJson() const
//{
//	QJsonObject json;
//	json.insert("createTime", createTime);
//	json.insert("color", color);
//	json.insert("name", name);
//	json.insert("address", address);
//	json.insert("tBegin", tBegin);
//	json.insert("tEnd", tEnd);
//	json.insert("note", note);
//	json.insert("priority", priority);
//	json.insert("repeatCycle", repeatCycle);
//	json.insert("repeatTimes", repeatTimes);
//	json.insert("deletedRepeatIndex", deletedRepeatIndex);
//	return json;
//}

bool CalEvent::crossDate() const
{
	return tBegin.date() != tEnd.date();
}

int CalEvent::getRepeatIndex(QDate date) const
{
	QDateTime t1 = tBegin, t2 = tEnd;
	for(int i=0; i<repeatTimes; ++i)
	{
		if(!deletedRepeatIndex.contains(i)
			&& t1.date() <= date && t2.date() >= date)
			return i;
		nextDate(t1, t2);
	}
	return -1;
}

void CalEvent::delRepeatIndex(int index)
{
	if(index < 0 || index >= repeatTimes)
		throw std::out_of_range("");
	deletedRepeatIndex.insert(index);
}

void CalEvent::delRepeatIndexAfter(int index)
{
	if(index < 0 || index >= repeatTimes)
		throw std::out_of_range("");
	repeatTimes = index;
}

int CalEvent::error() const
{
	if(name.length() == 0)
		return 1;
	if(tBegin >= tEnd)
		return 3;
	if(priority > PRIORITY_MAX || priority < 0)
		return 5;
	if(repeatTimes <= 0)
		return 6;
	return 0;
}

void CalEvent::nextDate(QDateTime &t1, QDateTime &t2) const
{
	switch(repeatCycle)
	{
	case Day:
		t1 = t1.addDays(1);
		t2 = t2.addDays(1);
		break;
	case Week:
		t1 = t1.addDays(7);
		t2 = t2.addDays(7);
		break;
	case Month:
		t1 = t1.addMonths(1);
		t2 = t2.addMonths(1);
		break;
	case Year:
		t1 = t1.addYears(1);
		t2 = t2.addYears(1);
		break;
	case None:
		break;
	default:
		throw std::runtime_error("Error in event's datetime increasing.");
	}
}
