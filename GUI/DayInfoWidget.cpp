#include "DayInfoWidget.h"
#include "ui_DayInfoWidget.h"

#include <QDebug>
#include <QColorDialog>
#include "Dialog/deleventdialog.h"
#include "calender.h"

DayInfoWidget::DayInfoWidget(const QDate &_date, ICalManager *_calManager, QWidget *parent):
	QWidget(parent),
	ui(new Ui::DayInfoWidget)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	QObject::installEventFilter(&windowDrag);
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
	showColor(calManager->getColor(date));
	ui->itemList->clear();
	itemList = calManager->getItemListInDate(date);
	for(auto item: itemList)
	{
		if(item->type() == CalItem::Event)
		{
			auto event = (const CalEvent*)item;
			auto wi = new QListWidgetItem ();
			auto ie = new ListItemEvent(event, date, calManager);
			ui->itemList->addItem(wi);
			ui->itemList->setItemWidget(wi, ie);
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
	if(ke->key() == Qt::Key_Escape)
		close();
	else if(ke->key() == Qt::Key_Delete || ke->key() == Qt::Key_Backspace)
	{
		delSelectedItem();
		ke->accept();
	}
}

void DayInfoWidget::on_pushButton_clicked()
{
	QColor color =  QColorDialog::getColor(Qt::transparent, this);
	calManager->setColor(date, color);
	showColor(color);
}

void DayInfoWidget::showColor(QColor color)
{
	QPalette pal;
	pal.setBrush(QPalette::Background, QBrush(color));
	ui->colorShow->setAutoFillBackground(true);
	ui->colorShow->setPalette(pal);
}

void DayInfoWidget::delSelectedItem()
{
	qDebug() << "Press Delete.";
	int id = ui->itemList->currentRow();
	if(itemList[id]->type() == CalItem::Event)
	{
		qDebug() << "Try to delete a event.";
		auto event = (const CalEvent*)itemList[id];
		if(event->repeatCycle == CalEvent::None)
		{
			calManager->delItem(event);
		}
		else
		{
			DelEventDialog dialog;
			dialog.exec();
			auto delType = dialog.getDelType();
			if(delType == DelEventDialog::All)
			{
				calManager->delItem(event);
			}
			else if(delType == DelEventDialog::One)
			{
				calManager->delItem(event);
				auto newEvent = (CalEvent*)event;
				newEvent->delRepeatIndex(newEvent->getRepeatIndex(date));
				calManager->addItem(newEvent);
			}
		}
		update();
	}
}
