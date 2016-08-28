#ifndef MOUSEIGNOREEVENTFILTER_H
#define MOUSEIGNOREEVENTFILTER_H

#include <QObject>

class MouseIgnoreEventFilter : public QObject
{
	Q_OBJECT
public:
	explicit MouseIgnoreEventFilter(QObject *parent = 0);
	bool eventFilter(QObject *obj, QEvent *event) override;
private:
	bool enabled = true;
};

#endif // MOUSEIGNOREEVENTFILTER_H
