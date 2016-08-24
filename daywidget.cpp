#include "daywidget.h"
#include "ui_daywidget.h"
#include <qdebug>
#include <QTextStream>

DayWidget::DayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DayWidget)
{
	ui->setupUi(this);
}

DayWidget::~DayWidget()
{
	delete ui;
}

void DayWidget::setDate(const QDate& _date)
{
	date = _date;
	ui->dayLabel->setText(QString::number(date.day()));
	ui->lunarLabel->setVisible(false);
}
