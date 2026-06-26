#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "WeatherDesign.h"
#include "Ticket.h"
#include <string>
#include "Hangar.h"
#include "Runway.h"
#include "User.h"
#include "Plane.h"
#include "MyException.h"

class Administrator : public User
{
	static Administrator* instance;
	Administrator(const std::string& name = "admin",
		const std::string& password = "admin");

public:
	static Administrator* getInstance();

	static bool hasInstance() { return instance != nullptr; }

	void buildRunway(const unsigned int length, bool ils, bool heavy, bool vip);
	void buildHangar(const std::string id, const int capacity, const double tax);
	void closeRunway(const int& runwayId);
	void changeWeather(const WeatherCondition& weather);
	void cloneAircraft(const int planeId, int count);
	void sentPlaneToHangar(const int& planeId, const std::string& hangarId);
	void scheduleFlight(const std::string& flightId, const int& planeId,
		const double& price, const std::string& destination);
	void retrivePlaneFromHangar(const int& planeId, const std::string& hangarId);
	void cancelFlight(const std::string& flightId);
	double flightRevenue(const std::string& flightId) const;
	void printFleet(std::ostream& os, std::string airlineName) const;
	void airportReport(std::ostream& os) const;
	void auditAirline(std::ostream& os, std::string airlineName) const;
	~Administrator();
	std::string getPlaneType(const Plane* plane);
	void buyAircraft(std::string airline_name, std::string model, int capacity);
	void registerAirline(std::string name, double balance);
	void auditAirline(std::string airline) const;
	const void help() const override;
	std::unique_ptr<User> clone() const override;
	void print(std::ostream& os) const override;

};
