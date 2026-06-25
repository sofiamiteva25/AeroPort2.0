#pragma once
#include "Plane.h"

class PlaneCollection {
	static std::vector<std::unique_ptr<Plane>> planes;
public:
	static const std::unique_ptr<Plane>& getPlaneByID(int id);
	static void addPlane(std::unique_ptr<Plane> plane);
	static const std::vector<std::unique_ptr<Plane>>& getAllPlanes();
	static void printAllPlanes(std::ostream& os);
	static void reset();
	static bool planeID(int id);
	static const std::unique_ptr<Plane>& getPlaneByFlightId(std::string flightId);
};
