#pragma once
// Observer.h

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
	Observer();

};
