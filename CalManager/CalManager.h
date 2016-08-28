#ifndef CALMANAGER_H
#define CALMANAGER_H

#include "ICalManager.h"
#include <QMap>
#include <QSet>

class CalManager : public ICalManager
{
public:
	CalManager();
	~CalManager();

private:
	QSettings* settings;
	QMap< QDate, QSet<const CalItem*> > dateToItemSet;
	QMap< QDate, QColor > dateToColor;

	// ICalManager interface
public:
	virtual void addItem(const CalItem *) override;
	virtual void delItem(const CalItem *) override;
	virtual void clear() override;
	virtual void setColor (QDate date, QColor color) override;
	virtual QColor getColor (QDate date) const override;
	virtual QSettings* getSettings() override;
	virtual void save() override;
	virtual void load() override;
	virtual bool addFile(QDate, const QString &fileName) override;
	virtual QVector<const CalItem *> getItemListInDate(QDate) const override;
	virtual QVector<const CalItem *> getItemList(std::function<bool (const CalItem *)> filter = ALWAYS_TRUE) const override;

private:
	QVariantMap toVariantMap () const;
	void fromVariantMap (QVariantMap const& data);
	QDir getFileDir(QDate date) const;


	QColor DEFAULT_COLOR_WORKDAY = Qt::white;
	QColor DEFAULT_COLOR_WEEKEND = Qt::lightGray;
};

#endif // CALMANAGER_H
