#pragma once
#include <vector>
#include "Object.h"

static class Observable {
public:
	static void Notify(int key);
	static void Add(Object* object);
	static void Remove();
};