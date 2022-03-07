#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include "regulableLampComposite.h"

#include <iostream>
#include <conio.h>

// VERSIÓN CORREGIDA, DOUBLE DISPATCH SIN RESOLVER ...

//Version 2.0//

void testRegulableLamp() {

    RegulableLamp* regulableLamp = new RegulableLamp(50) ;
	std::cout << "Estado inicial: " ; regulableLamp->actualState() ;

	regulableLamp->on() ;
	std::cout << "Estado actual: " ; regulableLamp->actualState() ;
	std::cout << "Sub-Estado on: " ; regulableLamp->getOnSubState() ;

    regulableLamp->increment() ;
    std::cout << "Intensidad: " << regulableLamp->intensity() << std::endl ;

	std::cout << "Estado actual: " ; regulableLamp->actualState() ;
	std::cout << "Sub-Estado on: " ; regulableLamp->getOnSubState() ;
	std::cout << std::endl ;

    regulableLamp->decrement() ;
    std::cout << "Intensidad: " << regulableLamp->intensity() << std::endl ;
	std::cout << "Estado actual: " ; regulableLamp->actualState() ;
    std::cout << "Sub-Estado on: " ; regulableLamp->getOnSubState() ;
	std::cout << std::endl ;

	regulableLamp->off() ;
	std::cout << "Estado actual: " ; regulableLamp->actualState() ;
	std::cout << "Estado composite: " ; regulableLamp->getOnSubState() ;

}

int _tmain(int argc, _TCHAR* argv[]) 
{
    testRegulableLamp() ;

	getch() ;

	return 0;
}
