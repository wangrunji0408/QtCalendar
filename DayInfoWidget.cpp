#include "DayInfoWidget.h"
#include "ui_DayInfoWidget.h"

#include <QListWidgetItem>
#include <QDebug>

DayInfoWidget::DayInfoWidget(const QDate &_date, const QVector<const CalItem *> &itemList, QWidget *parent):
	QWidget(parent),
	ui(new Ui::DayInfoWidget)
{
	ui->setupUi(this);
	date = _date;
	setItemList(itemList);
	qDebug() << "DayInfoWidget Construct End: " << date;
}

DayInfoWidget::~DayInfoWidget()
{
	delete ui;
}

void DayInfoWidget::setItemList(const QVector<const CalItem *> &itemList)
{
	for(auto item: itemList)
	{
		if(item->type == CalItem::Event)
		{
			auto event = (const CalEvent*)item;
			auto wi = new QListWidgetItem (QString("Event: ") + event->name);
			ui->itemList->addItem(wi);
		}
		else if(item->type == CalItem::Note)
		{
			ui->itemList->addItem("Note: ???");
		}
		else if(item->type == CalItem::File)
		{
			ui->itemList->addItem("File: ???");
		}
	}
}
