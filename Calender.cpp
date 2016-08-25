#include "calender.h"
#include "ui_calender.h"
#include "DayWidget.h"
#include "EventSettingDialog.h"
#include <qdebug>

Calender::Calender(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Calender)
{
	ui->setupUi(this);
	init();
	goToday();
}

Calender::~Calender()
{
	delete ui;
}

void Calender::init()
{
	firstDayOfWeek = 7;
	for(int j=0; j<7; ++j)
	{
		auto& l = weekdayLabel[j];
		l = new QLabel(this);
		l->setAlignment(Qt::AlignHCenter);
		ui->gridLayout_2->addWidget(l, 0, j);
	}
	for(int i=0; i<5; ++i)
	{
		for(int j=0; j<7; ++j)
		{
			dayWidget[i][j] = new DayWidget(this);
			ui->gridLayout_2->addWidget(dayWidget[i][j], i+1, j);
		}
	}
	calManager = new CalManager;
}

void Calender::update()
{
	QString title = QString::number(year) + "年" + QString::number(month) + "月";
	ui->titleLabel->setText(title);

	for(int j=0; j<7; ++j)
	{
		int weekday = (firstDayOfWeek-1 + j) % 7 + 1;
		weekdayLabel[j]->setText(QString::number(weekday));
	}

	QDate date = getFirstDayOfMonth();
	for(int i=0; i<5; ++i)
		for(int j=0; j<7; ++j)
		{
			auto& w = dayWidget[i][j];
			w->setDate(date);
			w->setItemList(calManager->getItemListInDate(date));
			date = date.addDays(1);
		}
}

QDate Calender::getFirstDayOfMonth ()
{
	QDate date(year, month, 1);
	while(date.dayOfWeek() != firstDayOfWeek)
		date = date.addDays(-1);
	return date;
}

void Calender::goToday()
{
	year = QDate::currentDate().year();
	month = QDate::currentDate().month();
	update();
}

void Calender::nextMonth()
{
	++month;
	if(month == 13)
		++year, month = 1;
	update();
}

void Calender::lastMonth()
{
	--month;
	if(month == 0)
		--year, month = 12;
	update();
}

void Calender::on_goTodayButton_clicked()
{
	goToday();
}

void Calender::on_goLeftButton_clicked()
{
	lastMonth();
}

void Calender::on_goRightButton_clicked()
{
	nextMonth();
}

void Calender::on_addItemButton_clicked()
{
	EventSettingDialog dialog;
	dialog.show();
	dialog.exec();
	if(dialog.result() == QDialog::Rejected)
		return;
	calManager->addItem(dialog.getEvent());
}
