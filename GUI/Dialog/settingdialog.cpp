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
	const QSettings* settings = calManager->getSettings();
	ui->mouseCross->setChecked( settings->value("MouseCross", false).toBool() );
	ui->opacity->setValue( settings->value("Opacity", 1.0).toFloat() * 100 );
	ui->firstDay->setCurrentIndex( settings->value("FirstDayOfWeek", 1).toInt() - 1 );
	ui->language->setCurrentIndex( languageName.indexOf(settings->value("Language", "zh").toString()) );
}

void SettingDialog::save()
{
	QSettings* settings = calManager->getSettings();
	settings->setValue("MouseCross", ui->mouseCross->isChecked());
	settings->setValue("Opacity", ui->opacity->value() / 100.0);
	settings->setValue("FirstDayOfWeek", ui->firstDay->currentIndex() + 1);
	settings->setValue("Language", languageName[ui->language->currentIndex()]);
}

void SettingDialog::applyLanguage()
{

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
	emit changed();
}
