#include "Hangar.h"
#include "HangarCollection.h"
#include "PlaneCollection.h"
#include "AirlineColl.h"
#include "Airline.h"
#include "MyException.h"
Hangar::Hangar(const Hangar& other)
{
    id = other.id;
    capacity = other.capacity;
    for (const auto& i : other.planesInHangar) {
        planesInHangar.push_back(i);
    }
    tax = other.tax;
}

const std::vector<int>& Hangar::getPlanesInHangar() const
{
    return planesInHangar;
}

Hangar::Hangar(int _capacity, double _tax, std::string _id)
{
    if (!HangarCollection::hangarId(_id) && _tax>0 && _capacity>0) {
        this->id = _id;
        capacity = _capacity;
        tax = _tax;
    }
    else {
        throw MyException("HangarAlreadyExists");
    }
}

void Hangar::addPlane(const int& id)
{
    if (PlaneCollection::planeID(id)&&planesInHangar.size()<capacity) {
        for (const auto& i : planesInHangar) {
            if (i == id) {
                throw MyException("PlaneAlreadyInHangar");
            }
        }
        planesInHangar.push_back(id);
        PlaneCollection::getPlaneByID(id)->setCondition(Condition::inHangar);
        return;
    }
    else {
        throw MyException("CannotAddPlaneInHangar");
    }
}

void Hangar::removePlane(const int& id)
{
    auto it = std::find_if(planesInHangar.begin(), planesInHangar.end(), [&id](const int& i) {
        return i == id;
        });
    if (it != planesInHangar.end()) {
        planesInHangar.erase(it);
        PlaneCollection::getPlaneByID(id)->setCondition(Condition::freePlane);
        PlaneCollection::getPlaneByID(id)->resetHealth();
        return;
    }
    else {
        throw MyException("NoPlaneInHangar");
    }
}

void Hangar::payTax(const int& planeId)
{
    AirlineColl::getAirlineByName(PlaneCollection::getPlaneByID(planeId)->getAirline())->
        payTax(planeId);
}

std::unique_ptr<Hangar> Hangar::clone() const
{
    return std::make_unique<Hangar>(*this);
}

const std::string& Hangar::getId() const
{
    return id;
}

const int Hangar::getCapacity() const
{
    return capacity;
}

bool Hangar::isAvailable() const
{
    if (planesInHangar.size() < capacity) {
        return true;
    }
    return false;
}

const double Hangar::getTax() const
{
    return tax;
}

std::ostream& operator<<(std::ostream& os, const Hangar& hangar)
{
    os << "Id: " << hangar.id << "\n";
    os << "Capacity: " << hangar.capacity << "\n";
    os << "Tax: " << hangar.tax << "\n";
    return os;
}
