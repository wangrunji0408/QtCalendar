#include "listitemevent.h"
#include "ui_listitemevent.h"
#include "../Dialog/EventSettingDialog.h"
#include "../Dialog/deleventdialog.h"
#include <QDebug>

ListItemEvent::ListItemEvent(const CalEvent *_event, QDate _date, ICalManager *_calManager, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ListItemEvent)
{
	ui->setupUi(this);
	calManager = _calManager;
	event = _event;
	date = _date;
	ui->nameLabel->setText(event->name);
	if(event->crossDate())
		ui->timeLabel->setText("CrossDay");
	else
		ui->timeLabel->setText(event->tBegin.toString("h:mm") + "-" + event->tEnd.toString("h:mm"));
}

ListItemEvent::~ListItemEvent()
{
	delete ui;
}

void ListItemEvent::keyPressEvent(QKeyEvent *ke)
{
	qDebug() << "ListItemEvent::keyPressEvent";
}

void ListItemEvent::mouseDoubleClickEvent(QMouseEvent *)
{
	EventSettingDialog dialog(event);
	dialog.exec();
	if(dialog.result() == QDialog::Accepted)
	{
		auto newEvent = dialog.getEvent();
		calManager->delItem(event);
		calManager->addItem(newEvent);
	}
}
