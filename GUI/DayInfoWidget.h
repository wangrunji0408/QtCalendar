#ifndef DAYINFOWIDGET_H
#define DAYINFOWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMap>
#include <QListWidgetItem>
#include "../CalManager/CalManager.h"
#include "EventFilter/windowdrageventfilter.h"

namespace Ui {
class DayInfoWidget;
}

class DayInfoWidget : public QWidget
{
	Q_OBJECT

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

signals:
	void changed ();

private:
	Ui::DayInfoWidget *ui;
	QDate date;
	ICalManager* calManager;
	QVector<const CalItem*> itemList;
	WindowDragEventFilter windowDrag;
};

#endif // DAYINFOWIDGET_H
