#ifndef  DISPATCH_H_INCLUDED
#define  DISPATCH_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;


struct Estado {

   virtual void process(struct EventOff *) = 0;

   virtual void process(struct EventOn *) = 0;

};


struct ReactEstado : Estado {

   ReactEstado(struct Maquina *fsm_) : fsm{fsm_} {}

   void process(struct EventOff *on);

   void process(struct EventOn *off);

   struct Maquina* fsm  = nullptr;

};


struct Event {

   virtual string name() = 0;

   virtual void process(struct Estado *currentState) = 0;

};


struct EventOff : Event {

   string name() {
		 return "ClickOff";
   }

   void process(Estado *currentState) {
		currentState->process(this);
   }

};


struct EventOn : Event {

   string name() {
		return "ClickOn";
   }

   void process(Estado * currentState) {
		currentState->process(this);
   }

   virtual~EventOn(){}

};

struct Maquina {

	void ReactTo(Event *_ev) {
		ReactEstado currentState{this};
		_ev->process(&currentState);
	}

   void ConsumeEvent(Event *_ev) {
		cout << "Consume event" << _ev->name() << endl;
   }

   void NotConsumeEvent(Event *_ev) {
		cout << "Not consume event " << _ev->name() << endl;
   }

};


void ReactEstado::process(EventOn *on) {

   fsm->ConsumeEvent(on);

}

void ReactEstado::process(EventOff *off) {

   fsm->NotConsumeEvent(off);

}


#endif // DISPATCH_H_INCLUDED
