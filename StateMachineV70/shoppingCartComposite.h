//---------------------------------------------------------------------------

#ifndef shoppingCartCompositeH
#define shoppingCartCompositeH


#include "event.h"
#include "state.h"
#include "composite_state.h"
#include "finite_state_machine.h"

#include <iostream>

//forward declaration
class ShoppingCart ;

// Eventos globales
IEvent* eventOff = nullptr ;
IEvent* eventOn = nullptr ;
// Eventos internos
IEvent* eventInc = nullptr ;
IEvent* eventDec = nullptr ;

// Estados globales
IState* stateOff = nullptr ;
IState* stateOn = nullptr ;
// Estados internos
IState* regulableState = nullptr ;


class IncrementAction : public IAction {
public:
	IncrementAction( ShoppingCart* shoppingCart ) ;
    virtual ~IncrementAction() ;

    void doAction() ;

private:
	ShoppingCart* _shoppingCart ;
} ;

class DecrementAction : public IAction {
public:
	DecrementAction( ShoppingCart* shoppingCart ) ;
    virtual ~DecrementAction() ;

    void doAction() ;

private:
    ShoppingCart* _shoppingCart ;
} ;


class ChangeAction : public IAction {
public:
	ChangeAction( ShoppingCart* shCart ) ;
    ~ChangeAction() ;
    void doAction() ;
private:
	ShoppingCart* _shCart ;
} ;


// Acciones del stateOn compuesto ...

class IncomeAction : public IAction {

    virtual ~IncomeAction() { }

    void doAction() override {
		std::cout << "income Action StateOn" << std::endl ;
    }
} *incomeAction = new IncomeAction ;

class ExitAction : public IAction {

	virtual ~ExitAction() { }

    void doAction() override {
		std::cout << "exit Action StateOn" << std::endl ;
    }
} *exitAction = new ExitAction ;

// REGULABLE LAMP
class ShoppingCart {
public:
	ShoppingCart( int intensity ) : _minPower(0), _maxPower(100), _intensity( intensity ), _lifetime(10) {
        // ACCIONES
        _onChangeAction = new ChangeAction( this ) ; // update
        _incAction = new IncrementAction( this ) ;
        _decAction = new DecrementAction( this ) ;

        // EVENTOS
        eventOff = new Event(0) ;
        eventOn = new Event(1) ;
        // Eventos internos
        eventInc = new Event(2) ;
		eventDec = new Event(3) ;

		// ESTADOS
		stateOff = new State(0) ;
		stateOn = new CompositeState(100) ;

        // Estados internos
		regulableState = new State(101) ;

        // TRANSICIONES
		_turningOff = new Transition( stateOn, eventOff, stateOff, nullptr, nullptr ) ;
        _turningOn = new Transition( stateOff, eventOn, stateOn, nullptr, nullptr ) ;

		_stateMachine = new FiniteStateMachine( _onChangeAction ) ;

		_stateMachine->setCurrentState( stateOff ) ;
		stateOn->setCurrentState( regulableState ) ;

		stateOn->assignEntryAction( incomeAction ) ;
		stateOn->assignExitAction( exitAction ) ;

		_turningOff = new Transition( stateOn, eventOff, stateOff, nullptr, nullptr ) ;
		_turningOn = new Transition( stateOff, eventOn, stateOn, nullptr, nullptr ) ;

		// SE AGREGAN LAS TRANSICIONES A LA MÁQUINA DE ESTADOS
		_stateMachine->addTransition( _turningOff ) ;
		_stateMachine->addTransition( _turningOn ) ;

		// SE CREAN LAS TRANSICIONES DEL ESTADO COMPUESTO
		_turnReg = new Transition( stateOn, eventOn, regulableState, nullptr, nullptr ) ; // timer
		_turnInc = new Transition( regulableState, eventInc, regulableState, _incAction, nullptr ) ;
		_turnDec = new Transition( regulableState, eventDec, regulableState, _decAction, nullptr ) ;

		// Se añaden las transiciones del estado compuesto
		stateOn->addTransition( _turnReg ) ;
		stateOn->addTransition( _turnInc ) ;
		stateOn->addTransition( _turnDec ) ;

    }

	virtual ~ShoppingCart() { //
		std::cout << "Shopping Cart destroy" ;
    }

    void on() {
        std::cout << "Evento ON" << std::endl ;
		_stateMachine->processEvent( eventOn ) ;

    }

    void off() {
		std::cout << "Evento OFF" << std::endl ;
		_stateMachine->processEvent( eventOff ) ;
    }

    void increment() {
		std::cout << "Evento INCREMENT" << std::endl ;
		_stateMachine->processEvent( eventInc ) ;
    }

    void decrement() {
		std::cout << "Evento DISMINUIR" << std::endl ;
        _stateMachine->processEvent( eventDec ) ;
    }

    void actualState() {
        showNameState( _stateMachine->currentState()->getId() ) ;
    }

	void getOnSubState() {
        showNameState( stateOn->currentState()->getId() ) ;
	}

	void intensityIncrement() {
		if ( ShoppingCart::_intensity < _maxPower ) ShoppingCart::_intensity++ ;
        std::cout << "Intensidad incrementa" << std::endl ; //
    }

	void intensityDecrement() {
		if ( ShoppingCart::_intensity > _minPower ) ShoppingCart::_intensity-- ;
        std::cout << "Intensidad disminuye "<< std::endl ; //
    }
    unsigned int intensity() {
        return _intensity ;
    }

    void showNameState( int id ) {
        switch(id) {
            case 0: std::cout << "state Off" << std::endl ;
                break ;
            case 100: std::cout << "state On" << std::endl ;
                break ;
            case 101: std::cout << "state Regulable" << std::endl ;
                break ;
        }
    }

private:
	ShoppingCart( const ShoppingCart& ) ;
	ShoppingCart& operator = ( const ShoppingCart& ) ;
    unsigned int _maxPower ;
    unsigned int _minPower ;

    IAction* _incAction ;
    IAction* _decAction ;

    // transiciones internas
	ITransition* _turnReg ;
    ITransition* _turnInc ;
	ITransition* _turnDec ;

    FiniteStateMachine* _stateMachine ;

    int _intensity ;
    int _lifetime ;

    // Creación de las acciones que va a utilizar
	IAction* _onChangeAction ;

    ITransition* _turningOff ;
	ITransition* _turningOn ;

} ;

// ACCIONES implementación
IncrementAction::IncrementAction( ShoppingCart* shoppingCart ) : _shoppingCart(shoppingCart) { }

IncrementAction::~IncrementAction() { }

void IncrementAction::doAction() {
	_shoppingCart->intensityIncrement() ;
}


DecrementAction::DecrementAction( ShoppingCart* shoppingCart ) : _shoppingCart(shoppingCart) { }

DecrementAction::~DecrementAction() { }

void DecrementAction::doAction() {
	_shoppingCart->intensityDecrement() ;
}

ChangeAction::ChangeAction( ShoppingCart* shCart ) : _shCart(shCart) { }

ChangeAction::~ChangeAction() { }

void ChangeAction::doAction() {
    std::cout << "CHANGE ACTION:: " << "El estado actual es:" ; _shCart->actualState() ;
    std::cout << "la intensidad es: " << _shCart->intensity() << std::endl ;
}


//---------------------------------------------------------------------------
#endif
