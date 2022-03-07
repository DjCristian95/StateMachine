//---------------------------------------------------------------------------

#ifndef regionH
#define regionH


#include "interfaces.h"
#include "finite_state_machine.h"

#include "state.h"


class Region : public State {
public:
	Region( int id ) : State(id), _subMachine(nullptr) {
		_subMachine = new FiniteStateMachine ;

	}

    virtual ~Region() {
        if ( _subMachine != nullptr ) delete _subMachine ;
	}

    void onEntry() override { //
        if ( _entryAction != nullptr ) _entryAction->doAction() ;
        _subMachine->onEntry() ;
    }

    void onExecute() override { //
        if ( _executeAction != nullptr ) _executeAction->doAction() ;
        _subMachine->onExecute() ;
    }

    void onExit() override {
        _subMachine->onExit() ; //
        if ( _exitAction != nullptr ) _exitAction->doAction() ;
    }

    // state machine functions ...

    virtual void addTransition( ITransition* transition ) override {
        _subMachine->addTransition( transition ) ;
	}

    virtual IState* currentState() override {
        return _subMachine->currentState() ;
    }

    virtual void setCurrentState( IState* state ) override {
        _subMachine->setCurrentState( state ) ;
    }

    virtual bool processEvent( IEvent* event ) override {
        return _subMachine->processEvent(event) ;
    }

protected:
    IState* _subMachine ;

private:
    Region( const Region& ) ;
    Region& operator = ( const Region& ) ;
} ;



//---------------------------------------------------------------------------
#endif
