#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
class Airline;
class AirlineColl
{
	static std::vector<std::unique_ptr<Airline>> airlines;
public:
	static const std::vector<std::unique_ptr<Airline>>& getAllAirlines();
	static const std::unique_ptr<Airline>& getAirlineByName(std::string airlineName);
	static void addAirline(std::unique_ptr<Airline> a);
	static void airlineReset();
};
class MyException;
