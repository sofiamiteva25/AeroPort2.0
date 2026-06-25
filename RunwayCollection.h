#pragma once
#include "Runway.h"

class RunwayCollection
{
	static std::vector<std::unique_ptr<Runway>> runways;
public:
	static const std::vector<std::unique_ptr<Runway>>& getAllRunways();
	static void addRunway(std::unique_ptr<Runway>& runway);
	static const std::unique_ptr<Runway>& getRunwayByPlaneId(const int& id);
	static const std::unique_ptr<Runway>& getRunwayById(const int& id);
	static void printAllRunways(std::ostream& os);
};
