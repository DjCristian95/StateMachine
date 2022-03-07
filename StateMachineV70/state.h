//---------------------------------------------------------------------------

#ifndef stateH
#define stateH


#include "interfaces.h"


class State : public IState {
public:
    State( int id ) : _id( id ), _entryAction(nullptr), _executeAction(nullptr), _exitAction(nullptr) { }

    State() : _id( -1 ), _entryAction(nullptr), _executeAction(nullptr), _exitAction(nullptr)  { }

    virtual ~State() { }

    void onEntry() {
        if ( _entryAction != nullptr ) _entryAction->doAction() ;
    }

    void onExecute() { // activity
        _executeAction->doAction() ;
    }

    void onExit() {
        if ( _exitAction != nullptr ) _exitAction->doAction() ;
    }

    int getId() {
        return _id ;
    }

    void assignEntryAction( IAction* action ) {
        _entryAction = action ;
    }

    void assignExecuteAction( IAction* action ) {
        _executeAction = action ;
    }

    void assignExitAction( IAction* action ) {
        _exitAction = action ;
	}

protected:
    int _id ;
    IAction* _entryAction ;
    IAction* _executeAction ;
    IAction* _exitAction ;

private:
    State( const State& ) ;
    State& operator = ( const State& ) ;

} ;


//---------------------------------------------------------------------------
#endif
