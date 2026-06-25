#include "RunwayCollection.h"
#include "MyException.h"
std::vector<std::unique_ptr<Runway>> RunwayCollection::runways;

const std::vector<std::unique_ptr<Runway>>& RunwayCollection::getAllRunways()
{
	return runways;
}

void RunwayCollection::addRunway(std::unique_ptr<Runway>& runway)
{
	for (const auto& i : runways) {
		if (i->getID() == runway->getID()) {
			throw MyException("RunwayWithIdExists");
		}
	}
	runways.push_back(std::move(runway));
}

const std::unique_ptr<Runway>& RunwayCollection::getRunwayByPlaneId(const int& id)
{
	for (const auto& i : runways) {
		if (i->getPlaneOnRunway() == id) {
			return i;
		}
	}
	throw MyException("NoRunwayWithPlaneId");
}

const std::unique_ptr<Runway>& RunwayCollection::getRunwayById(const int& id)
{
	for (const auto& i : runways) {
		if (i->getID() == id) {
			return i;
		}
	}
	throw MyException("RunwayWithIdNotFound");
}

void RunwayCollection::printAllRunways(std::ostream& os)
{
	for (const auto& i : runways) {
		os << *i;
	}
}
