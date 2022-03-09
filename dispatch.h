#ifndef  DISPATCH_H_INCLUDED
#define  DISPATCH_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

#include<iostream>

class State;
class Event;

class Event {
public:
	virtual bool process(State*state)= 0;
};


class State {
public:
	virtual bool process(Event* event)= 0;
};

class LampState;
class StateOff;
class StateOn;

class LampEvent;
class EventOn;
class EventOff;

class LampState : public State {
public:
	 virtual bool process(EventOff* event)= 0;
	 virtual bool process(EventOn* event)= 0;
};


class LampEvent: public Event {
	public:
	 virtual bool process(StateOff* event)= 0;
	 virtual bool process(StateOn* event)= 0;
};


class StateOff: public LampState {
public:
	virtual bool process(Event* event) {
		return event->process(this);
	}

	virtual bool process(EventOff* ) {
		return false;
	}

	virtual bool process(EventOn* ) {
		return true;
	}
};

class StateOn: public LampState {
public:
	virtual bool process(Event* event) {
		return (event)->process(this);
	}

	virtual bool process(EventOff*) {
		return true;
	}

	virtual bool process(EventOn* ) {
		return false;
	}
};


class EventOff : public LampEvent {
	public:
	virtual bool process (State* state) {
		return (state)->process(this);
	}

	virtual bool process ( StateOn* state) {
		return (state)->process(this);
	}

	virtual bool process ( StateOff* state) {
		return (state)->process(this);
	}
};


class EventOn : public LampEvent {
	public:
	virtual bool process (State* state) {
		return (state)->process(this);
	}

	virtual bool process (StateOn* state) {
		return (state)->process(this);
	}

	virtual bool process (StateOff* state) {
		return (state)->process(this);
	}
};


struct ReactEstado : State {

	ReactEstado(struct Maquina *fsm_) : fsm{fsm_} {}

	bool process ( Event*event) {
		return (event)->process(this);
	};

	bool process(struct EventOn *off);

	bool process(struct EventOff *on);

	struct Maquina* fsm  = nullptr;

};


struct Maquina {

	   void ReactTo(Event *_ev) {
		   ReactEstado currentState{this};
		   _ev->process(&currentState);
	   }

	   bool ConsumeEvent(Event *_ev) {
			std::cout << "Consume event"  << std::endl;
			return true;//condicional para lanzar maquina
	   }

	   bool NotConsumeEvent(Event *_ev) {
			std::cout << "Not consume event "  << std::endl;
			return false;
	   }

};


bool ReactEstado::process(EventOn *on) {
	fsm->ConsumeEvent(on);
	return true;
}


bool ReactEstado::process(EventOff *off) {
   fsm->NotConsumeEvent(off);
   return false;
}

 #endif // DISPATCH_H_INCLUDED
