#ifndef EVENTSETTINGDIALOG_H
#define EVENTSETTINGDIALOG_H

#include <QDialog>
#include <QColor>
#include "CalEvent.h"

namespace Ui {
class EventSettingDialog;
}

class EventSettingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit EventSettingDialog (CalEvent* event = nullptr, QWidget *parent = 0);
	~EventSettingDialog();
	void setEvent ();
	CalEvent* getEvent () const;
private:
	void showColor (QColor color);

private slots:
	void on_colorButton_clicked();

private:
	Ui::EventSettingDialog *ui;
	CalEvent* event;
};

#endif // EVENTSETTINGDIALOG_H
