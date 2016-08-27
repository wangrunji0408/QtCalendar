#include "CalManager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

CalManager::CalManager()
{

}

CalManager::~CalManager()
{
	save();
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
	qDebug() << "CalManager::save";
	QString fileName = "data.txt";
	QFile file(fileName);
	file.open(QFile::WriteOnly);
	QTextStream(&file) << QJsonDocument::fromVariant(toVariantMap()).toJson();
}

void CalManager::load()
{
	qDebug() << "CalManager::load() Begin.";
	QString fileName = "data.txt";
	QFile file(fileName);
	file.open(QFile::ReadOnly);
	QString jsonStr = QTextStream(&file).readAll();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &jsonError);
	if(jsonError.error == QJsonParseError::NoError)
	{
		if(jsonDoc.isObject())
		{
			qDebug() << "Json Parse success!";
			fromVariantMap(jsonDoc.toVariant().toMap());
		}
	}
	else
		throw std::runtime_error("Json Parse Error!");
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

QVariantMap CalManager::toVariantMap() const
{
	QVariantMap data;

	QVariantList itemList;
	for(const CalItem* item: getItemList())
	{
		if(item->type() == CalItem::Event)
		{
			auto event = (const CalEvent*)item;
			itemList.append(event->toVariantMap());
		}
	}
	data.insert("itemList", itemList);

	QVariantMap colorMap;
	for(QDate date: dateToColor.keys())
		colorMap.insert(date.toString(), dateToColor[date]);
	data.insert("colorMap", colorMap);

	return data;
}

void CalManager::fromVariantMap(const QVariantMap &data)
{
	clear();
	for(QVariant var: data["itemList"].toList())
	{
		QVariantMap map = var.toMap();
		if(map["type"] == "Event")
		{
			auto event = new CalEvent;
			event->fromVariantMap(map);
			addItem(event);
		}
	}
	QVariantMap colorMap = data["colorMap"].toMap();
	for(QString dateString: colorMap.keys())
	{
		QColor color = colorMap[dateString].value<QColor>();
		dateToColor.insert(QDate::fromString(dateString), color);
	}
}
