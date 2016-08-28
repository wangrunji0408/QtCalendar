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
	load();
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

void SettingDialog::load()
{
	const QSettings& settings = calManager->getSettings();
	ui->mouseCross->setChecked( settings.property("MouseCross").toBool() );
	ui->transparent->setValue( settings.property("Transparent").toFloat() * 100 );
	ui->firstDay->setCurrentIndex( settings.property("FirstDayOfWeek").toInt() - 1 );
}

void SettingDialog::save()
{
	QSettings& settings = calManager->getSettings();
	settings.setProperty("MouseCross", ui->mouseCross->isChecked());
	settings.setProperty("Transparent", ui->transparent->value() / 100.0);
	settings.setProperty("FirstDayOfWeek", ui->firstDay->currentIndex() + 1);
}

void SettingDialog::on_loadButton_clicked()
{
	calManager->load();
	emit changed();
}

void SettingDialog::on_saveButton_clicked()
{
	calManager->save();
}

void SettingDialog::on_buttonBox_accepted()
{
	save();
}
