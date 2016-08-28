#include "calender.h"
#include "ui_calender.h"
#include "DayWidget.h"
#include "DayInfoWidget.h"
#include "Dialog/settingdialog.h"
#include "Dialog/EventSettingDialog.h"
#include <QPalette>
#include <QMimeData>
#include <QMessageBox>

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
	delete calManager;
	delete ui;
}

void Calender::init()
{
	setWindowFlags(Qt::FramelessWindowHint);
	QObject::installEventFilter(&windowDrag);
	calManager = new CalManager;
	firstDayOfWeek = 7;
	for(int j=0; j<7; ++j)
	{
		auto& l = weekdayLabel[j];
		l = new QLabel(this);
		l->setAlignment(Qt::AlignHCenter);
		ui->gridLayout_2->addWidget(l, 0, j);
	}
	for(int i=0; i<ROW; ++i)
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
	for(int i=0; i<ROW; ++i)
		for(int j=0; j<7; ++j)
		{
			auto& w = dayWidget[i][j];
			w->setDate(date, date.month() == month);
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
	update();
}

void Calender::on_settingButton_clicked()
{
	auto dialog = new SettingDialog(calManager);
	connect(dialog, SIGNAL(changed()), this, SLOT(update()));
	dialog->exec();
}

void Calender::on_fix_clicked(bool checked)
{
	windowDrag.setEnabled(!checked);
	calManager->getSettings().setProperty("WindowDrag", checked);
}

void Calender::showDayInfoWidget(QDate date)
{
	static DayInfoWidget* dayInfo = nullptr;
	if(dayInfo != nullptr)
		dayInfo->close();
	dayInfo = new DayInfoWidget(date, calManager);
	connect(dayInfo, SIGNAL(changed()), this, SLOT(update()));
	dayInfo->show();
}
