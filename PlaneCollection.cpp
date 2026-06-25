#include "PlaneCollection.h"
#include "MyException.h"
std::vector<std::unique_ptr<Plane>> PlaneCollection::planes;

const std::unique_ptr<Plane>& PlaneCollection::getPlaneByID(int id)
{
    for (const auto& i : planes) {
        if (i->getID() == id) {
            return i;
        }
    }
    throw MyException("NoPlaneWithId");
}

void PlaneCollection::addPlane(std::unique_ptr<Plane> plane)
{
    for (const auto& i : planes) {
        if (i->getID() == plane->getID()) {
            throw MyException("CannotAddPlane");
        }
    }
    planes.push_back(std::move(plane));
}

const std::vector<std::unique_ptr<Plane>>& PlaneCollection::getAllPlanes()
{
    if (planes.size() != 0) {
        return planes;
    }
    else {
        throw MyException("NoAddedPlanes");
    }
}

void PlaneCollection::printAllPlanes(std::ostream& os)
{
    for (const auto& i : planes) {
        i->printInfo(os);
    }
}

void PlaneCollection::reset()
{
    planes.clear();
}

bool PlaneCollection::planeID(int id)
{
    for (const auto& i : planes) {
        if (i->getID() == id) {
            return true;
        }
    }
    return false;
}

const std::unique_ptr<Plane>& PlaneCollection::getPlaneByFlightId(std::string flightId)
{
    for (const auto& i : planes) {
        if (i->getFlight() == flightId) {
            return i;
        }
    }
    throw MyException("NoPlaneWithThisFlightId");
}
