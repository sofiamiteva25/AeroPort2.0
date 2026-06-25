#pragma once
#include <string>
#include <memory>
#include "Plane.h"
#include <vector>
#include <algorithm>
#include <iostream>
class MyException;
class Hangar
{
	std::string id;
	int capacity;
	double tax;
	std::vector<int> planesInHangar;
public:
	Hangar(const Hangar& other);
	const std::vector<int>& getPlanesInHangar() const;
	Hangar(int _capacity, double _tax, std::string _id);
	void addPlane(const int& id);
	void removePlane(const int& id);
	void payTax(const int& id);
	std::unique_ptr<Hangar> clone() const;
	const std::string& getId() const;
	friend std::ostream& operator<<(std::ostream& os, const Hangar& hangar);
	const int getCapacity() const;
	bool isAvailable() const;
	const double getTax() const;


};
