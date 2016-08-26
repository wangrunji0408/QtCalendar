#include "DayInfoWidget.h"
#include "ui_DayInfoWidget.h"

#include <QListWidgetItem>
#include <QDebug>
#include "listitemevent.h"

DayInfoWidget::DayInfoWidget(const QDate &_date, ICalManager *_calManager, QWidget *parent):
	QWidget(parent),
	ui(new Ui::DayInfoWidget)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	date = _date;
	calManager = _calManager;
	update();
}

DayInfoWidget::~DayInfoWidget()
{
	delete ui;
}

void DayInfoWidget::update ()
{
	ui->dateLabel->setText(date.toString("yyyy年M月d日"));
	for(auto item: calManager->getItemListInDate(date))
	{
		if(item->type() == CalItem::Event)
		{
			auto event = (const CalEvent*)item;
			auto wi = new QListWidgetItem ();
			ui->itemList->addItem(wi);
			ui->itemList->setItemWidget(wi, new ListItemEvent(event, date, calManager));
		}
		else if(item->type() == CalItem::Note)
		{
			auto note = (const CalNote*)item;
			ui->itemList->addItem("Note: " + note->note);
		}
		else if(item->type() == CalItem::File)
		{
			auto file = (const CalFile*)item;
			ui->itemList->addItem("File: " + file->fileInfo.fileName());
		}
	}
}

void DayInfoWidget::keyPressEvent(QKeyEvent *ke)
{
	qDebug() << "DayInfoWidget::keyPressEvent";
}
