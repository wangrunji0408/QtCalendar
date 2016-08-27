#include "windowdrageventfilter.h"
#include <QEvent>
#include <QMouseEvent>

WindowDragEventFilter::WindowDragEventFilter(QObject *parent) : QObject(parent)
{

}

bool WindowDragEventFilter::eventFilter(QObject *obj, QEvent *event)
{
	if(!enabled)	return false;
	auto widget = (QWidget*)obj;
	if(event->type() == QEvent::MouseButtonPress)
	{
		auto me = (QMouseEvent*)event;
		mousePos0 = me->globalPos();
		windowPos0 = widget->pos();
		draging = me->button() == Qt::LeftButton;
		return true;
	}
	else if(!draging)
		return false;
	else if(event->type() == QEvent::MouseMove)
	{
		auto me = (QMouseEvent*)event;
		widget->move(windowPos0 + me->globalPos() - mousePos0);
		return true;
	}
	else if(event->type() == QEvent::MouseButtonRelease)
	{
		draging = false;
		return true;
	}
	return false;
}
