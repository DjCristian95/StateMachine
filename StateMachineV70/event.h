//---------------------------------------------------------------------------

#ifndef eventH
#define eventH

#include "interfaces.h"

class Event : public IEvent {
public:
    Event( int id, IAction* action = nullptr ) : _id(id), _action(action) { }

    virtual ~Event() { }

    int getId() {
        return _id ;
    }

    void doAction() {
        if ( _action ) _action->doAction() ;
    }

private:
    int _id ;
    IAction* _action ;
} ;

//---------------------------------------------------------------------------
#endif
