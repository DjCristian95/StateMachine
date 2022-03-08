#include <iostream>
#include "dispatch.h"
#include <vector>
#include <conio.h>
using namespace std;

///// Versión 3.0 //////


int main() {

	Maquina fsm;

	Estado* currentState = new StateOff();
	Event* incoming = new EventOn;

	fsm.ReactTo(incoming);

	getch() ;
    return 0;
}
