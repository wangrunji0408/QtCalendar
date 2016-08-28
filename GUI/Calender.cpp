#include "calender.h"
#include "ui_calender.h"
#include "DayWidget.h"
#include "DayInfoWidget.h"
#include "Dialog/settingdialog.h"
#include "Dialog/EventSettingDialog.h"
#include <QPalette>
#include <QMimeData>
#include <QMessageBox>
#include <QApplication>
#include <QTranslator>
//#include <QEvent>

Calender::Calender(QApplication *_app, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Calender)
{
	ui->setupUi(this);
	app = _app;
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
	applyLanguage();
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

void Calender::applyLanguage()
{
	static QTranslator* trans;
	if(trans == nullptr)
		trans = new QTranslator;
	else
	{
		app->removeTranslator(trans);
	}
	QString langName = calManager->getSettings()->value("Language", "zh").toString();
	trans->load(langName);
	app->installTranslator(trans);
	this->setLocale(langName == "zh"? QLocale::Chinese: QLocale::English);
}

void Calender::update()
{
	applyLanguage();
	QString title = QString::number(year) + tr("年") + QString::number(month) + tr("月");
	ui->titleLabel->setText(title);
	for(int j=0; j<7; ++j)
	{
		int firstDayOfWeek = calManager->getSettings()->value("FirstDayOfWeek").toInt();
		int weekday = (firstDayOfWeek-1 + j) % 7 + 1;
		QString dayName[] = {"", tr("周一"), tr("周二"),tr("周三"),tr("周四"),tr("周五"),tr("周六"),tr("周日")};
//		weekdayLabel[j]->setText(QDate::shortDayName(weekday));
		weekdayLabel[j]->setText(dayName[weekday]);
	}

	float opacity = calManager->getSettings()->value("Opacity", 1).toFloat();
	this->setWindowOpacity(opacity);
	QDate date = getFirstDayOfMonth();
	for(int i=0; i<ROW; ++i)
		for(int j=0; j<7; ++j)
		{
			auto& w = dayWidget[i][j];
			w->setDate(date, date.month() == month);
//			w->setWindowOpacity(opacity);
			date = date.addDays(1);
		}

	bool drag =  calManager->getSettings()->value("WindowDrag", true).toBool();
	windowDrag.setEnabled(drag);
	ui->fix->setChecked(!drag);
}

QDate Calender::getFirstDayOfMonth ()
{
	QDate date(year, month, 1);
	int firstDayOfWeek = calManager->getSettings()->value("FirstDayOfWeek").toInt();
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

void Calender::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	if(e->type() == QEvent::LanguageChange)
	{
		ui->retranslateUi(this);
	}
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
	calManager->getSettings()->setValue("WindowDrag", !checked);
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
