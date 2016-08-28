#include "mouseignoreeventfilter.h"
#include <QEvent>
#include <QDebug>

MouseIgnoreEventFilter::MouseIgnoreEventFilter(QObject *parent) : QObject(parent)
{

}

bool MouseIgnoreEventFilter::eventFilter(QObject *obj, QEvent *event)
{
	if(!enabled)	return false;
	if(event->type() == QEvent::MouseButtonPress)
	{
		qDebug() << "Catch mouse event!";
		return true;
	}
}
