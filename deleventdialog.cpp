#include "deleventdialog.h"
#include "ui_deleventdialog.h"

DelEventDialog::DelEventDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DelEventDialog)
{
	ui->setupUi(this);
}

DelEventDialog::~DelEventDialog()
{
	delete ui;
}

void DelEventDialog::on_pushButton_clicked()
{
	delType = Cancel;
	close();
}

void DelEventDialog::on_pushButton_2_clicked()
{
	delType = One;
	close();
}

void DelEventDialog::on_pushButton_3_clicked()
{
	delType = All;
	close();
}
