#include "Observable.h"
void Observable::attach(Observer* o) {
	observers.insert(o);
}
void Observable::detach(Observer& o) {
	observers.erase(&o);
}
void Observable::detachAll() {
	observers.clear();
}
void Observable::notify(const std::string& message, const bool log) {
	sendUpdate(message, log, false);
}

void Observable::log(const std::string& message) {
	sendUpdate(message, true, true);
}

void Observable::sendUpdate(const std::string& message, const bool log, const bool onlyLog) {
	std::set<Observer*>::iterator it;
	for (it = observers.begin(); it != observers.end(); it++)
		(*it)->update(message, log, onlyLog);
}
