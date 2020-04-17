#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Subject
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
	Subject();
	~Subject();

private:
	list<Observer*>* observers;
};