//---------------------------------------------------------------------------

#ifndef finite_state_machineH
#define finite_state_machineH

#include "state.h"
#include "transition.h"
#include <iostream>


class StateModel { // en uso
enum { MAXIMUM = 255 } ;
public:
    StateModel() : _count(0) {
        _transitions = new ITransition*[MAXIMUM] ;
    }

    ~StateModel() {
        delete[] _transitions ;
	}

    ITransition* itemAtPos( size_t pos ) {
        return _transitions[pos] ;
    }

    void add( ITransition* transition ) {
        _transitions[ _count ] = transition ;
        _count++ ;
    }

    size_t size() {
        return _count ;
    }

private:
    size_t _count ;
    ITransition** _transitions ;
} ;

class FiniteStateMachine : public State {
public:
	FiniteStateMachine( IAction* onChangeAction = nullptr ) : _onChangeAction(onChangeAction) { //
		_stateModel = new StateModel() ;
	}

	virtual ~FiniteStateMachine() { //
		if ( _stateModel != nullptr ) delete _stateModel ; //
	}

	void addTransition( ITransition* transition ) {
		_stateModel->add( transition ) ;
    }

	void setCurrentState( IState* state ) {
		_currentState = state ;
    }

    IState* currentState() {
        return _currentState ;
    }

    bool processEvent( IEvent* event ) {
		return ( _currentState->processEvent(event) || this->dispatchEvent(event) ) ;
	}

	bool dispatchEvent( IEvent* event ) {
		bool found = false ;
		ITransition* transition = nullptr ;
        for ( int i = 0; i < _stateModel->size() && !found ; i++ ) {
            transition = _stateModel->itemAtPos( i ) ;
			// SOLUCIONAR DOBLE DISPATCH
            if ( _currentState->getId() == transition->getSource()->getId() ) {
                if ( event->getId() == transition->triggerEvent()->getId() ) {
                    found = true ;
					if ( transition->checkGuard() ) processTransition( transition ) ;
                }
            }
        }
        return found ;
    }

protected:
	bool processTransition( ITransition* transition ) { //
		_currentState->onExit() ; //
		transition->executeAction() ; //
        if ( _currentState != transition->nextState() ) {
            _currentState = transition->nextState() ;
            _currentState->onEntry() ;
            // _currentState->onExecute() ;
        }
        return true ; //
    }

private:
    FiniteStateMachine( const FiniteStateMachine& ) ;
    FiniteStateMachine& operator = ( const FiniteStateMachine& ) ;

    IState* _currentState ;
	StateModel* _stateModel ; //

	IAction* _onChangeAction ; //
} ;


//---------------------------------------------------------------------------
#endif
