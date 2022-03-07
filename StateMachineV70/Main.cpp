#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include "shoppingCartComposite.h"

#include <iostream>
#include <conio.h>

// VERSIÓN CORREGIDA, DOUBLE DISPATCH SIN RESOLVER ...

//Version 2.0//

void testShoppingCart() {

	ShoppingCart* shoppingCart = new ShoppingCart(50) ;
	std::cout << "Estado inicial: " ; shoppingCart->actualState() ;

	shoppingCart->on() ;
	std::cout << "Estado actual: " ; shoppingCart->actualState() ;
	std::cout << "Sub-Estado on: " ; shoppingCart->getOnSubState() ;

	shoppingCart->increment() ;
	std::cout << "Intensidad: " << shoppingCart->intensity() << std::endl ;

	std::cout << "Estado actual: " ; shoppingCart->actualState() ;
	std::cout << "Sub-Estado on: " ; shoppingCart->getOnSubState() ;
	std::cout << std::endl ;

	shoppingCart->decrement() ;
	std::cout << "Intensidad: " << shoppingCart->intensity() << std::endl ;
	std::cout << "Estado actual: " ; shoppingCart->actualState() ;
	std::cout << "Sub-Estado on: " ; shoppingCart->getOnSubState() ;
	std::cout << std::endl ;

	shoppingCart->off() ;
	std::cout << "Estado actual: " ; shoppingCart->actualState() ;
	std::cout << "Estado composite: " ; shoppingCart->getOnSubState() ;

}

int main()
{
	testShoppingCart() ;

	getch() ;

	return 0;
}
