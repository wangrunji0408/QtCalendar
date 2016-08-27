#include "ICalManager.h"

ICalManager::ICalManager()
{

}

void ICalManager::merge(ICalManager &calManager)
{
	for(auto item: calManager.getItemList())
		this->addItem(item);
	calManager.clear();
}
