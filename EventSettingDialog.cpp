#include "EventSettingDialog.h"
#include "ui_EventSettingDialog.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>

EventSettingDialog::EventSettingDialog(CalEvent *_event, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EventSettingDialog)
{
	ui->setupUi(this);
	if(_event == nullptr)
	{
		event = new CalEvent;
		event->tBegin = QDateTime::currentDateTime();
		event->tEnd = event->tBegin.addSecs(3600);
	}
	else
	{
		event = _event;
	}
	setEvent();
}

EventSettingDialog::~EventSettingDialog()
{
	delete ui;
}

void EventSettingDialog::setEvent()
{
	ui->name->setText(event->name);
	ui->address->setText(event->address);
	ui->tBegin->setDateTime(event->tBegin);
	ui->tEnd->setDateTime(event->tEnd);
	ui->note->setText(event->note);
	ui->priority->setValue(event->priority);
	ui->repeatType->setCurrentIndex(event->repeatCycle);
	ui->repeatTimes->setValue(event->repeatTimes);
	showColor(event->color);

	ui->createTime->setText(event->createTime.toString("yyyy/M/d HH:mm"));
}

CalEvent* EventSettingDialog::getEvent() const
{
	event->name = ui->name->text();
	event->address = ui->address->text();
	event->tBegin = ui->tBegin->dateTime();
	event->tEnd = ui->tEnd->dateTime();
	event->note = ui->note->document()->toPlainText();
	event->priority = ui->priority->value();
	event->repeatCycle = (CalEvent::RepeatCycle)ui->repeatType->currentIndex();
	event->repeatTimes = ui->repeatTimes->value();
	event->color = ui->colorShow->palette().background().color();
	return event;
}

void EventSettingDialog::showColor(QColor color)
{
	QPalette pal;
	pal.setBrush(QPalette::Background, QBrush(color));
	ui->colorShow->setAutoFillBackground(true);
	ui->colorShow->setPalette(pal);
}

void EventSettingDialog::accept()
{
	if(getEvent()->error())
		QMessageBox::warning(this, "参数无效", "参数无效");
	else
		QDialog::accept();
}

void EventSettingDialog::on_colorButton_clicked()
{
	showColor(QColorDialog::getColor(Qt::red, this));
}
