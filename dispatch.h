#ifndef  DISPATCH_H_INCLUDED
#define  DISPATCH_H_INCLUDED


class State;
class Event;

class Event{
public:
    virtual bool process(State*state)= 0;
};

class State{
public:
    virtual bool process(Event* event)= 0;
};

class ShoppingCartState;
class StateEmpty;  //estado vacío
class StateContainer;     //estado contenedor

class ShoppingCartEvent;
class EventContainer;
class EventEmpty;

class ShoppingCartState : public State {
public:
     virtual bool process(EventEmpty* event)= 0;
     virtual bool process(EventContainer* event)= 0;
};

class ShoppingCartEvent: public Event{
    public:
     virtual bool process(StateEmpty* event)= 0;
     virtual bool process(StateContainer* event)= 0;
};


class EventEmpty : public ShoppingCartEvent{
    public:
    virtual bool process (State* state){
        return ((ShoppingCartState*)state)->process(this);
    }

    virtual bool process (StateContainer* state){
        return ((ShoppingCartState*)state)->process(this);
    }
    virtual bool process (StateEmpty* state){
        return ((ShoppingCartState*)state)->process(this);
    }

};

class EventContainer : public ShoppingCartEvent{
    public:
    virtual bool process (State* state){
        return ((ShoppingCartState*)state)->process(this);
    }

    virtual bool process (StateContainer* state){
        return ((ShoppingCartState*)state)->process(this);
    }
    virtual bool process (StateEmpty* state){
        return ((ShoppingCartState*)state)->process(this);
    }

};

class StateEmpty: public ShoppingCartState{
public:
    virtual bool process(Event* event){
        return ((ShoppingCartEvent*)event)->process(this);
    }

    virtual bool process(EventEmpty* event){
        std::cout<<"not consume event..."<< std::endl;
        return false;
    }
    virtual bool process(EventContainer* event){
        std::cout<<" consume event..." <<std::endl;
        return true;
    }
};

class StateContainer: public ShoppingCartState{
public:
    virtual bool process(Event* event){
        return ((ShoppingCartEvent*)event)->process(this);
    }

    virtual bool process(EventEmpty* event){
        std::cout<<" consume event..."<< std::endl;
        return false;
    }
    virtual bool process(EventContainer* event){
        std::cout<<"   not consume event..." <<std::endl;
        return true;
    }
};

#endif // DISPATCH_H_INCLUDED
