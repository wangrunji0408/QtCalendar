#include "listitemfile.h"
#include "ui_listitemfile.h"

#include <QDrag>
#include <QMimeData>
#include <QUrl>

ListItemFile::ListItemFile(const CalFile* _file, QDate _date, ICalManager* _calManager, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ListItemFile)
{
	ui->setupUi(this);
	file = _file;
	date = _date;
	calManager = _calManager;
	ui->label->setText("File: " + file->fileInfo.fileName());
}

ListItemFile::~ListItemFile()
{
	delete ui;
}

void ListItemFile::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		int distance = (event->pos() - mousePos0).manhattanLength();
		if (distance < QApplication::startDragDistance())
			return;
		QMimeData *mimedata = new QMimeData;
		QList<QUrl> urlList;
		urlList.append(QUrl(file->fileInfo.filePath()));
		mimedata->setUrls(urlList);
		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimedata);
		drag->exec(Qt::CopyAction);
	}
}

void ListItemFile::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		mousePos0 = event->pos();
		event->accept();
	}
}
