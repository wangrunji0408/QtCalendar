#ifndef DELEVENTDIALOG_H
#define DELEVENTDIALOG_H

#include <QDialog>

namespace Ui {
class DelEventDialog;
}

class DelEventDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DelEventDialog(QWidget *parent = 0);
	~DelEventDialog();

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();

public:
	enum DelType {Cancel, One, All};
	DelType getDelType () const {return delType;}

private:
	Ui::DelEventDialog *ui;
	DelType delType;
};

#endif // DELEVENTDIALOG_H
