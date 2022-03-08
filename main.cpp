#include <iostream>
#include "dispatch.h"
#include <vector>
#include <conio.h>
using namespace std;

///// Versión 2.0 //////


int main() {

	Maquina fsm;

	for(Event* incoming : vector<Event*>{new EventOn , new EventOff}) {
		std::cout<<"FSM...."<<std::endl;
		fsm.ReactTo(incoming);
	}

	getch() ;
    return 0;
}
