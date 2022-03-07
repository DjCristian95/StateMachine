//---------------------------------------------------------------------------

#ifndef mapperH
#define mapperH

#include "Collection.h"
#include "Associative_Container.h"

#include "interfaces.h"

// VERSIÓN COLLECTION + ASSOCIATIVE CONTAINERS
class Mapper {
    enum { MAX_ITEMS = 512 } ;
public:
    Mapper() {
        _states.init() ;
        for ( int i = 0; i < MAX_ITEMS; i++ ) _statesTransitions[i].init() ;
    }

    ~Mapper() {
        _states.release() ;
        for ( int i = 0; i < MAX_ITEMS; i++ ) _statesTransitions[i].release() ;
    }

    void addRow( IState* state, IEvent* event, ITransition* transition ) {
        if ( _states.contain( state ) ) {
            int pos = _states.indexOf( state ) ;
            _statesTransitions[pos].add( event, transition ) ;
        } else {
            _states.add( state ) ;
            int pos = _states.indexOf( state ) ;
            _statesTransitions[pos].add( event, transition ) ;
        }
    }

    ITransition* doubleDispatch(  IState* state, IEvent* event ) {
        int pos = _states.indexOf( state ) ;
        return _statesTransitions[pos].itemAtPos( event ) ;
    }

private:
    Collection<IState*> _states ;
    AssociativeContainer<IEvent*,ITransition*> _statesTransitions[MAX_ITEMS] ;
} ;
//---------------------------------------------------------------------------
#endif
