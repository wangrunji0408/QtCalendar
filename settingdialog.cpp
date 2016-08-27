#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(ICalManager *_calManager, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingDialog)
{
	ui->setupUi(this);
	calManager = _calManager;
	for(int i=1; i<=7; ++i)
	{
		ui->firstDay->addItem(QDate::shortDayName(i));
	}
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

void SettingDialog::on_loadButton_clicked()
{
	calManager->load();
}

void SettingDialog::on_saveButton_clicked()
{
	calManager->save();
}
