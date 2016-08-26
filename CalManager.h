#ifndef CALMANAGER_H
#define CALMANAGER_H

#include "ICalManager.h"
#include <QMap>
#include <QSet>


class CalManager : public ICalManager
{
public:
	CalManager();

private:
	QSettings settings;
	QMap< QDate, QSet<const CalItem*> > dateToItemSet;
	QMap< QDate, QColor > dateToColor;

	// ICalManager interface
public:
	virtual void addItem(const CalItem *) override;
	virtual void delItem(const CalItem *) override;
	virtual void clear() override;
	virtual void setColor (QDate date, QColor color) override;
	virtual QColor getColor (QDate date) const override;
	virtual QSettings& getSettings() override;
	virtual void save() override;
	virtual void load() override;
	virtual QVector<const CalItem *> getItemListInDate(QDate) const override;
	virtual QVector<const CalItem *> getItemList(std::function<bool (const CalItem *)> filter) const override;

private:
	QColor DEFAULT_COLOR_WORKDAY = Qt::white;
	QColor DEFAULT_COLOR_WEEKEND = Qt::gray;
};

#endif // CALMANAGER_H
