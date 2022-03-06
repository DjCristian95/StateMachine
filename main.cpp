#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif
#include <iostream>
#include "dispatch.h"
#include <conio.h>

///// Versión 1.0 //////
using namespace std;

int main()
{

    State* currentState= new StateContainer();
	Event* incommingEvent = new EventEmpty();

	currentState->process(incommingEvent);
	delete currentState;
	delete incommingEvent;
	getch() ;
    return 0;
}
