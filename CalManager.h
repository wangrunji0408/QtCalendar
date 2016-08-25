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
	QMap< QDate, QSet<const CalItem*> > dateToItemSet;

	// ICalManager interface
public:
	virtual void addItem(const CalItem *) override;
	virtual void delItem(const CalItem *) override;
	virtual void clear() override;
	virtual void save() override;
	virtual void load() override;
	virtual QVector<const CalItem *> getItemListInDate(QDate) const override;
	virtual QVector<const CalItem *> getItemList(std::function<bool (const CalItem *)> filter) const override;
};

#endif // CALMANAGER_H
