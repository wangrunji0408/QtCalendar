#include "CalEvent.h"

bool CalEvent::inDate(QDate date) const
{
	QDateTime t1 = tBegin, t2 = tEnd;
	for(int i=0; i<repeatTimes; ++i)
	{
		if(!deletedRepeatIndex.contains(i)
			&& t1.date() <= date && t2.date() >= date)
			return true;
		nextDate(t1, t2);
	}
	return false;
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
		throw std::runtime_error("repeatCycle == None. Can't go next.");
	default:
		throw std::runtime_error("Error in event's datetime increasing.");
	}
}
