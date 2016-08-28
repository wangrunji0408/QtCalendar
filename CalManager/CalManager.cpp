#include "CalManager.h"
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QSettings>

CalManager::CalManager()
{
	settings = new QSettings("settings.ini", QSettings::IniFormat);
	if(!settings->contains("FirstDayOfWeek"))
		settings->setValue("FirstDayOfWeek", 7);
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
	delete item;
}

void CalManager::clear()
{
	dateToItemSet.clear();
	dateToColor.clear();
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

QSettings *CalManager::getSettings()
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

bool CalManager::addFile(QDate date, const QString &fileName)
{
	QFileInfo fileInfo(fileName);
	if(!fileInfo.exists())
		qDebug() << "No such file: " << fileName;
	auto file = new CalFile(fileName, date);
	bool result = file->copyTo(getFileDir(date));
	if(result)
		addItem(file);
	return result;
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
		itemList.append(item->toVariantMap());
	data.insert("itemList", itemList);

	QVariantMap colorMap;
	for(QDate date: dateToColor.keys())
		colorMap.insert(date.toString("yyyy-MM-dd"), dateToColor[date]);
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
		else if(map["type"] == "Note")
		{
			auto note = new CalNote;
			note->fromVariantMap(map);
			addItem(note);
		}
		else if(map["type"] == "File")
		{
			auto file = new CalFile;
			file->fromVariantMap(map);
			addItem(file);
		}
	}
	QVariantMap colorMap = data["colorMap"].toMap();
	for(QString dateString: colorMap.keys())
	{
		QColor color = colorMap[dateString].value<QColor>();
		dateToColor.insert(QDate::fromString(dateString, "yyyy-MM-dd"), color);
	}
}

QDir CalManager::getFileDir(QDate date) const
{
	return QDir("file/" + date.toString("yyyy-MM-dd"));
}
