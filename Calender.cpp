#include "calender.h"
#include "ui_calender.h"
#include "DayWidget.h"
#include "EventSettingDialog.h"
#include "DayInfoWidget.h"
#include "settingdialog.h"
#include <QDebug>
#include <QPalette>
#include <QMimeData>
#include <QMessageBox>

Calender::Calender(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Calender)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	init();
	goToday();
}

Calender::~Calender()
{
	delete calManager;
	delete ui;
}

void Calender::init()
{
	calManager = new CalManager;
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
			dayWidget[i][j] = new DayWidget(calManager, this);
			ui->gridLayout_2->addWidget(dayWidget[i][j], i+1, j);
			connect(dayWidget[i][j], SIGNAL(showDayInfoWidget (QDate)),
					this, SLOT(showDayInfoWidget (QDate)));
		}
	}
}

void Calender::update()
{
	QString title = QString::number(year) + "年" + QString::number(month) + "月";
	ui->titleLabel->setText(title);

	for(int j=0; j<7; ++j)
	{
		int weekday = (firstDayOfWeek-1 + j) % 7 + 1;
		weekdayLabel[j]->setText(QDate::shortDayName(weekday));
	}

	QDate date = getFirstDayOfMonth();
	for(int i=0; i<5; ++i)
		for(int j=0; j<7; ++j)
		{
			auto& w = dayWidget[i][j];
			w->setDate(date);

//			w->setStyleSheet("background-color: " + calManager->getColor(date).name());
			QPalette pal = w->palette();
			pal.setBrush(w->backgroundRole(), calManager->getColor(date));
			w->setAutoFillBackground(true);
			w->setPalette(pal);


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

void Calender::dragEnterEvent(QDragEnterEvent *event)
{
	qDebug() << "Calendar::dragEnterEvent()";
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

void Calender::on_settingButton_clicked()
{
	SettingDialog(calManager).exec();
	update();
}

void Calender::showDayInfoWidget(QDate date)
{
	static DayInfoWidget* dayInfo = nullptr;
	if(dayInfo != nullptr)
		dayInfo->close();
	dayInfo = new DayInfoWidget(date, calManager);
	dayInfo->show();
}
