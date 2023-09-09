#pragma once
#include <string>
class Observable;

class Observer {
public:
	// Called by the observed object, whenever
	// the observed object is changed:
	virtual void update(const std::string& message, bool log, bool onlyLog) = 0;
	virtual ~Observer() {}
};