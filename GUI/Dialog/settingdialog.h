#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "../../CalManager/CalManager.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingDialog(ICalManager* _calManager, QWidget *parent = 0);
	~SettingDialog();
private:
	void load ();
	void save ();

private slots:
	void on_loadButton_clicked();
	void on_saveButton_clicked();
	void on_buttonBox_accepted();
	void on_exportButton_clicked();
	void on_importButton_clicked();

signals:
	void changed ();

private:
	Ui::SettingDialog *ui;
	ICalManager* calManager;
	const QVector<QString> languageName = {"zh", "en"};
};

#endif // SETTINGDIALOG_H
