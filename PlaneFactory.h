#pragma once
#include "Plane.h"

class PlaneFactory
{
	static int count;
	std::string type;
	int capacity;

public:
	PlaneFactory(std::string _type, int _capacity);
	void createPlane(const std::string& airlineName);
	static void resetCount();
};
