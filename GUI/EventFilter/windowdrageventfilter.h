#ifndef WINDOWDRAGEVENTFILTER_H
#define WINDOWDRAGEVENTFILTER_H

#include <QWidget>
#include <QPoint>

class WindowDragEventFilter : public QObject
{
	Q_OBJECT
public:
	explicit WindowDragEventFilter(QObject *parent = 0);
	bool eventFilter(QObject *obj, QEvent *event) override;
	void setEnabled (bool _enabled) {enabled = _enabled;}

private:
	bool enabled = true;
	bool draging = false;
	QPoint mousePos0, windowPos0;
};

#endif // WINDOWDRAGEVENTFILTER_H
