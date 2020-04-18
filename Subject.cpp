#include "Subject.h"
#include <iostream>


Subject::Subject() {
	observers = new list<Observer*>;
}

Subject::~Subject() {
	delete observers;
}

void Subject::attach(Observer* o) {
	observers->push_back(o);
}

void Subject::detach(Observer* o) {
	observers->remove(o);
}

void Subject::notify() {
	list<Observer*>::iterator i = observers->begin();
	
	for (; i != observers->end(); i++) {
		cout << "Notify Called!" << endl;
		(*i)->Update();
	}
}
