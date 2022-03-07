//---------------------------------------------------------------------------

#ifndef transitionH
#define transitionH


#include "interfaces.h"

class Transition : public ITransition {
public:
    Transition( IState* source, IEvent* event, IState* target, IAction* action = nullptr, IGuard* guard = nullptr )
        : _source(source), _event(event), _target(target), _action(action), _guard(guard) {
	}

    virtual ~Transition() { }

    IState* getSource() {
        return _source ;
    }

    IState* nextState() {
        return _target ;
    }

    IEvent* triggerEvent() {
        return _event ;
    }

    void executeAction() {
        if ( _action != nullptr ) _action->doAction() ;
    }

	bool checkGuard() {
        bool result = true ;
        if ( _guard != nullptr ) result = _guard->check() ;
        return result ;
    }

private:
    IEvent* _event ;
    IState* _source ;
    IState* _target ;
    IAction* _action ;
    IGuard* _guard ;

} ;

//---------------------------------------------------------------------------
#endif
