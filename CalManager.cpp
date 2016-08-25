#include "CalManager.h"

CalManager::CalManager()
{

}

void CalManager::addItem(const CalItem *item)
{
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

void CalManager::save()
{
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
