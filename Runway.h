#pragma once
#include <optional>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>
class MyException;
class PlaneCollection;

enum StatusRunway {
	RunwayFree,
	RunwayOccupied,
	RunwayMaintenance
};


class Runway
{
public:
	struct Builder {
		unsigned int length = 0;
		bool ils = false;
		bool heavyDuty = false;
		bool vipTerminal = false;
		Builder& withLength(const unsigned int& len);
		Builder& withILS();
		Builder& withHeavyDuty();
		Builder& withVIPTerminal();
		std::unique_ptr<Runway> build() const;
	};

	unsigned int getLength() const;
	bool hasHeavyDuty() const;
	bool hasVIP() const;
	bool hasILS() const;
	std::unique_ptr<Runway> clone() const;
	const int& getPlaneOnRunway() const;
	const int getID() const;
	friend std::ostream& operator<<(std::ostream& os, const Runway& runway);
	StatusRunway getStatus() const;
	void setPlaneOnRunway(const int& planeId);
	void setStatus(const StatusRunway& newStatus);
	void removePlaneFromRunway();

protected:
	Runway(const unsigned int& length, bool ils, bool heavyDuty, bool vipTerminal);
	static int count;
	int idRunway;
	unsigned int length;
	StatusRunway status;
	bool ils;
	bool heavyDuty;
	bool vipTerminal;
	int planeOnRunway;
};
