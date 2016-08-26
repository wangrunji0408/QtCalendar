#include "DayWidget.h"
#include "ui_daywidget.h"
#include <qdebug>
#include <QTextStream>
#include <QPalette>
#include <QMimeData>
#include <QMessageBox>

DayWidget::DayWidget(ICalManager* _calManager, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DayWidget)
{
	ui->setupUi(this);
	ui->lunarLabel->setVisible(false);
	calManager = _calManager;
}

DayWidget::~DayWidget()
{
	delete ui;
}

void DayWidget::setDate(const QDate& _date)
{
	date = _date;
	update();
}

void DayWidget::update()
{
	ui->dayLabel->setText(QString::number(date.day()));

	QPalette pal = ui->dayLabel->palette();
	pal.setBrush(QPalette::WindowText, date == QDate::currentDate()? Qt::red: Qt::black);
	ui->dayLabel->setPalette(pal);

	itemList = calManager->getItemListInDate(date);

	ui->label->setText(QString::number(itemList.length()));
}

void DayWidget::mouseReleaseEvent(QMouseEvent *e)
{
	qDebug() << "Mouse Release: " << date;
	DayInfoWidget dayInfo(date, itemList, nullptr);
	dayInfo.show();
	e->accept();
}

void DayWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void DayWidget::dropEvent(QDropEvent *event)
{
	for(QUrl url: event->mimeData()->urls())
	{
		QString filePath = url.toLocalFile();
		auto cf = new CalFile(filePath, date);
		QDir targetDir = QDir("file");//calManager->getSettings().value("filePath");
		cf->copyTo(targetDir);
		calManager->addItem(cf);
	}
	event->accept();
	update();
}
