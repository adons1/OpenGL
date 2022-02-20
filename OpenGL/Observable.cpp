#include "Observable.h"

static std::vector<Object*> observers;
void Observable::Notify(int key) {

	for (Object* obj : observers) {
		obj->Control(key);
	}
}
void Observable::Add(Object* object) {
	observers.push_back(object);
}
void Observable::Remove() {
	throw std::logic_error("Not implemented exception");
}