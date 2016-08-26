#include "CalManager.h"
#include <QDebug>

CalManager::CalManager()
{

}

void CalManager::addItem(const CalItem *item)
{
	qDebug() << "AddItem at " << QDateTime::currentDateTime().toString();
	for(QDate date: item->getDateList())
		dateToItemSet[date].insert(item);
}

void CalManager::delItem(const CalItem *item)
{
	for(QDate date: item->getDateList())
		dateToItemSet[date].remove(item);
}

void CalManager::clear()
{
	dateToItemSet.clear();
}

void CalManager::setColor(QDate date, QColor color)
{
	dateToColor[date] = color;
}

QColor CalManager::getColor(QDate date) const
{
	if(dateToColor.contains(date))
		return dateToColor[date];
	if(date.dayOfWeek() <= 5)
		return DEFAULT_COLOR_WORKDAY;
	else
		return DEFAULT_COLOR_WEEKEND;
}

QSettings& CalManager::getSettings()
{
	return settings;
}

void CalManager::save()
{
//	settings.sync();
}

void CalManager::load()
{
}

QVector<const CalItem *> CalManager::getItemListInDate(QDate date) const
{
	QVector<const CalItem *> list;
	if(dateToItemSet.contains(date) == false)
		return list;
	for(auto item: dateToItemSet[date])
		list.append(item);
	return list;
}

QVector<const CalItem *> CalManager::getItemList(std::function<bool (const CalItem *)> filter) const
{
	QVector<const CalItem *> list;
	for(const auto& set: dateToItemSet)
	{
		for(const CalItem *item: set)
			if(filter(item))
				list.append(item);
	}
	return list;
}
