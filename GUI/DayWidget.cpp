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

void DayWidget::setDate(const QDate& _date, bool _inMonth)
{
	date = _date;
	inMonth = _inMonth;
	update();
}

void DayWidget::update()
{
	ui->dayLabel->setText(QString::number(date.day()));

	QColor textColor;
	if(date == QDate::currentDate())
		textColor = Qt::red;
	else if(inMonth)
		textColor = Qt::black;
	else
		textColor = Qt::darkGray;
	QPalette pal = ui->dayLabel->palette();
	pal.setBrush(QPalette::WindowText, textColor);
	ui->dayLabel->setPalette(pal);

	pal = this->palette();
	pal.setBrush(this->backgroundRole(), calManager->getColor(date));
	this->setAutoFillBackground(true);
	this->setPalette(pal);

	itemList = calManager->getItemListInDate(date);

	pal.setBrush(QPalette::WindowText, Qt::red);
	ui->dotLabel_1->setPalette(pal);
	pal.setBrush(QPalette::WindowText, Qt::yellow);
	ui->dotLabel_2->setPalette(pal);
	pal.setBrush(QPalette::WindowText, Qt::blue);
	ui->dotLabel_3->setPalette(pal);

	QString c1, c2, c3;
	for(auto item: itemList)
	{
		if(item->type() == CalItem::Event)	c1 += "●";
		if(item->type() == CalItem::Note)	c2 += "●";
		if(item->type() == CalItem::File)	c3 += "●";
	}
	ui->dotLabel_1->setText(c1);
	ui->dotLabel_2->setText(c2);
	ui->dotLabel_3->setText(c3);

}

void DayWidget::mouseReleaseEvent(QMouseEvent *e)
{
	qDebug() << "Mouse Release: " << date;
	emit showDayInfoWidget(date);
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
		calManager->addFile(date, filePath);
	}
	event->accept();
	update();
}
