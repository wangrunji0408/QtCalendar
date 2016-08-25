#include "calfile.h"

CalFile::CalFile (QFileInfo fileInfo, QDate date)
{
	this->fileInfo = fileInfo;
	this->date = date;
}
