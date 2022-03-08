#ifndef  DISPATCH_H_INCLUDED
#define  DISPATCH_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

struct Event {

   virtual string name() = 0;
   virtual bool process(struct StateOn* onState) = 0;
   virtual bool process(struct StateOff* offState) = 0;
   virtual bool process(struct Estado *currentState) = 0;

};

struct Estado {

	virtual bool process (struct Event*) = 0;

	virtual bool process(struct EventOff *) = 0;

	virtual bool process(struct EventOn *) = 0;

};


class StateOn: public Estado {
public:
	virtual bool process(Event* event) {
		return (event)->process(this);
	}

	virtual bool process(struct EventOff* event) {
		return true;
	}

	virtual bool process(struct EventOn* event) {
		return false;
	}
};


class StateOff: public Estado {
public:
	virtual bool process(Event* event) {
		return (event)->process(this);
	}

	virtual bool process(struct EventOff* event) {
		return false;
	}

	virtual bool process(struct EventOn* event) {
		return true;
	}
};



struct ReactEstado : Estado {

	ReactEstado(struct Maquina *fsm_) : fsm{fsm_} {}

	bool process (Event* event) {
	   return (event)->process(this);
	};

	bool process(struct EventOff *on);

	bool process(struct EventOn *off);

    struct Maquina* fsm  = nullptr;

};


struct EventOff : Event {

   string name() {
		 return "ClickOff";
   }

   bool process(Estado *currentState) {
		currentState->process(this);
   }

   bool process (StateOn* onState) {
	   onState->process(this);
   }

   bool process (StateOff* offState) {
		offState-> process(this);
   }

};


struct EventOn : Event {

	string name() {
		return "ClickOn";
	}

	bool process(Estado * currentState) {
		currentState->process(this);
	}

	bool process (StateOn* onState) {
		onState-> process(this);
	}

	bool process (StateOff* offState) {
		offState->process(this);
	}

};

struct Maquina {

   void ReactTo(Event *_ev) {
		ReactEstado currentState{this};
		_ev->process(&currentState);
   }

   void ConsumeEvent(Event *_ev) {
		cout << "Consume event " << _ev->name() << endl;
   }


   void NotConsumeEvent(Event *_ev) {
		cout << "Not consume event " << _ev->name() << endl;
   }

};


bool ReactEstado::process(EventOn *on) {

   fsm->ConsumeEvent(on);

}

bool ReactEstado::process(EventOff *off) {

   fsm->NotConsumeEvent(off);

}


#endif // DISPATCH_H_INCLUDED
