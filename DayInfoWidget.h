#ifndef DAYINFOWIDGET_H
#define DAYINFOWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMap>
#include <QListWidgetItem>
#include "calitemall.h"
#include "CalManager.h"
#include "windowdrag.h"
#include "listitemevent.h"

namespace Ui {
class DayInfoWidget;
}

class DayInfoWidget : public QWidget
{
	Q_OBJECT
	WINDOW_DRAG

public:
	explicit DayInfoWidget(const QDate &_date, ICalManager* _calManager, QWidget *parent = 0);
	~DayInfoWidget();
	void keyPressEvent(QKeyEvent *ke) override;

private slots:
	void on_pushButton_clicked();
	void update ();

private:
	void showColor (QColor color);
	void delSelectedItem ();

private:
	Ui::DayInfoWidget *ui;
	QDate date;
	ICalManager* calManager;
	QVector<const CalItem*> itemList;
};

#endif // DAYINFOWIDGET_H
