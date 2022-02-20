#include "Observable.h"
#include <vector>

static std::vector<Object*> observers;
void Observable::Notify(int key) {

	for (Object * object : observers) {
		object->Control(key);
	}
}
void Observable::Add(Object* object) {
	observers.push_back(object);
}
void Observable::Remove() {
	throw std::logic_error("Not implemented exception");
}