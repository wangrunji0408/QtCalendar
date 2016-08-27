#include "listitemfile.h"
#include "ui_listitemfile.h"

ListItemFile::ListItemFile(const CalFile* _file, QDate _date, ICalManager* _calManager, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ListItemFile)
{
	ui->setupUi(this);
}

ListItemFile::~ListItemFile()
{
	delete ui;
}
