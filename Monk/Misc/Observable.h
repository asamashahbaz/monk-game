#pragma once
#include <set>
#include <string>

#include "Observer.h"

class Observable {
	std::set<Observer*> observers;
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer& o);
	virtual void detachAll();
	virtual void notify(const std::string& message, bool log = false);
	virtual void log(const std::string& message);
	virtual void sendUpdate(const std::string& message, bool log, bool onlyLog);
	virtual ~Observable() = default;
};