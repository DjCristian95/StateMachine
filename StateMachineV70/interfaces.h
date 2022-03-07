//---------------------------------------------------------------------------

#ifndef interfacesH
#define interfacesH


struct IState ;

struct IAction {
	virtual void doAction() = 0 ;
} ;

struct IEvent {
	virtual int getId() = 0 ;
	virtual void doAction() = 0 ;
} ;

struct IGuard {
    virtual bool check() = 0 ;
} ;

struct ITransition {
    virtual IState* nextState() = 0 ;
    virtual IState* getSource() = 0 ;
    virtual bool checkGuard() = 0 ;
    virtual void executeAction() = 0 ;
    virtual IEvent* triggerEvent()  = 0 ;
} ;

// Abstract State
struct IState {
    virtual ~IState() { }

    // state functions ...
    virtual void onEntry() = 0 ;
    virtual void onExecute() = 0 ;
    virtual void onExit() = 0 ;
    virtual void assignEntryAction( IAction* ) = 0 ;
    virtual void assignExecuteAction( IAction* ) = 0 ;
    virtual void assignExitAction( IAction* ) = 0 ;
    virtual int getId() = 0 ;

	// State Machine functions ...
    virtual void addTransition( ITransition* ) {
        return ;
    }

    virtual IState* currentState() {
        return this ;
    }

    virtual void setCurrentState( IState* ) {
        return ;
    }

    virtual bool processEvent( IEvent* ) {
        return false ;
    };

} ;



//---------------------------------------------------------------------------
#endif
