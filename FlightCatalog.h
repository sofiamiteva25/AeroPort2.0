#pragma once
#include "Flight.h"

class FlightCatalog {
	static std::vector<std::unique_ptr<Flight>> flights;
public:
	static const std::vector<std::unique_ptr<Flight>>& getAllFlights();
	static std::vector<std::unique_ptr<Flight>> getFlightsByDestination(const std::string& _dest);
	static std::vector<std::unique_ptr<Flight>> getFlightsByPrice(const double& price);
	static void addFlight(std::unique_ptr<Flight>& flight);
	static const std::unique_ptr<Flight>& getFlightByID(const std::string& id);
	static const std::unique_ptr<Flight>& getFlightByPlaneID(const int& id);
	static void resetFlights();
	static void printAllFlights(std::ostream& os);
	static void removeFlight(const std::string& flightId);
	static double getFlightRevenue(const std::string& flightId);

};
