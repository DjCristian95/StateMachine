//---------------------------------------------------------------------------

#ifndef composite_stateH
#define composite_stateH


#include "state.h"
#include "region.h"

#include <iostream>

class CompositeState : public State {
public:
	CompositeState( int id ) : State(id) {
		_activeRegion = new Region(0) ;
	}

	virtual ~CompositeState() { //
        if ( _activeRegion != nullptr ) delete _activeRegion ; //
	}

    void onEntry() override { //
        if ( _entryAction != nullptr ) _entryAction->doAction() ;
        _activeRegion->onEntry() ;
    }

    void onExecute() override { // activity
        if ( _executeAction != nullptr ) _executeAction->doAction() ;
        _activeRegion->onExecute() ;
    }

    void onExit() override {
        _activeRegion->onExit() ;
        if ( _exitAction != nullptr ) _exitAction->doAction() ;
	}

	virtual void addTransition( ITransition* transition ) override {
		_activeRegion->addTransition( transition ) ;
    }

	virtual IState* currentState() override {
        return _activeRegion->currentState() ;
	}

	virtual void setCurrentState( IState* state ) override {
		_activeRegion->setCurrentState( state ) ; //
	}

	virtual bool processEvent( IEvent* event ) override {
		return _activeRegion->processEvent( event ) ;
	}

protected:

    IState* _activeRegion ; //

private:
    CompositeState( const CompositeState& ) ;
    CompositeState& operator = ( const CompositeState& ) ;

} ;


//---------------------------------------------------------------------------
#endif
