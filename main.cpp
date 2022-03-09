#include <iostream>
#include "dispatch.h"
#include <vector>
#include <conio.h>
using namespace std;

///// Versión 4.0 //////


int main() {

	Maquina fsm;

	Event* incomingEvent = new EventOff;

	fsm.ReactTo(incomingEvent);

	getch() ;
    return 0;
}
