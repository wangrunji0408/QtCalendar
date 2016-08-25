#ifndef CALITEM_H
#define CALITEM_H

#include <QTime>

class CalItem
{
public:
	CalItem ();
	CalItem (QTime createTime);
protected:
	QTime createTime;
};

#endif // CALITEM_H
