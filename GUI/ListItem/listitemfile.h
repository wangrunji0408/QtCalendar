#ifndef LISTITEMFILE_H
#define LISTITEMFILE_H

#include <QWidget>
#include <QMouseEvent>
#include "../../CalManager/CalManager.h"

namespace Ui {
class ListItemFile;
}

class ListItemFile : public QWidget
{
	Q_OBJECT

public:
	explicit ListItemFile(const CalFile* _file, QDate _date, ICalManager* _calManager, QWidget *parent = 0);
	~ListItemFile();
	void mouseMoveEvent(QMouseEvent* event) override;	// 拖出文件-移动
	void mousePressEvent(QMouseEvent *event) override;	// 拖出文件-点击
	void mouseDoubleClickEvent(QMouseEvent *) override;	// 打开文件

private:
	Ui::ListItemFile *ui;
	const CalFile* file;
	ICalManager* calManager;
	QDate date;
	QPoint mousePos0;
};

#endif // LISTITEMFILE_H
