#pragma once
#include <vector>
#include "Object.h"

static class Observable {
private:
	//static std::vector<Object*> observers;
public:
	static void Notify(int key) {
		/*for (Object* obj : observers) {
			obj->Control(key);
		}*/
	}
	static void Add(Object* object) {
		//observers.push_back(object);
	}
	static void Remove() {
		//throw std::logic_error("Not implemented exception");
	}
};