#include "DayWidget.h"
#include "ui_daywidget.h"
#include <qdebug>
#include <QTextStream>

DayWidget::DayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DayWidget)
{
	ui->setupUi(this);
	ui->lunarLabel->setVisible(false);
}

DayWidget::~DayWidget()
{
	delete ui;
}

void DayWidget::setDate(const QDate& _date)
{
	date = _date;
	ui->dayLabel->setText(QString::number(date.day()));
}

void DayWidget::setItemList(QVector<const CalItem*> const& _itemList)
{
	itemList = _itemList;
}

void DayWidget::mouseReleaseEvent(QMouseEvent *e)
{
	qDebug() << "Mouse Release: " << date;
	DayInfoWidget dayInfo(date, itemList, nullptr);
	dayInfo.show();
}
