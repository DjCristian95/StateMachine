#include <iostream>
#include "dispatch.h"
#include <vector>
#include <conio.h>
using namespace std;

///// Versi�n 3.0 //////


int main() {

	Maquina fsm;

	Estado* currentState = new StateOff();
	Event* incoming = new EventOn;

	fsm.ReactTo(incoming);

	getch() ;
    return 0;
}
