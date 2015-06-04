 #include "stdafx.h"
#ifndef OSAKA_CHECKDELETE_H
#define OSAKA_CHECKDELETE_H

void _STARTCHECKDELETE(bool ascension);
void _CHECKDELETE(std::string classname, bool deconstructor = true);
void _ENDCHECKDELETE();

#endif