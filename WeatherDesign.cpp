#include "WeatherDesign.h"
#include "Person.h"
#include "RunwayCollection.h"
#include "FlightCatalog.h"
#include "TicketCatalog.h"
std::unique_ptr<WeatherDesign> WeatherDesign::instance;
WeatherDesign::WeatherDesign()
{
    currentCondition = WeatherCondition::Clear;
}

const std::unique_ptr<WeatherDesign>& WeatherDesign::getInstance()
{
    if (!instance) {
        instance = std::unique_ptr<WeatherDesign>(new WeatherDesign());
    }
    return instance;
}

void WeatherDesign::updateWeather(WeatherCondition condition)
{
    WeatherDesign::getInstance()->setWeather(condition);
}

void WeatherDesign::addObserver(const std::string& observerId)
{
    observers.push_back(observerId);
}

void WeatherDesign::setWeather(WeatherCondition newWeather)
{
    if (currentCondition == newWeather) {
        std::cout << "The same weather condition is already set. No update needed.\n";
        return;
    }
    currentCondition = newWeather;

    std::string weatherStr = (newWeather == WeatherCondition::Clear) ? "SUNNY" :
        (newWeather == WeatherCondition::Rain) ? "RAINY" :
        (newWeather == WeatherCondition::Fog) ? "FOGGY" :
        (newWeather == WeatherCondition::Snow) ? "SNOWY" : "STORM";

    std::cout << "Weather Conditions changed to " << weatherStr << "\n";

    if (newWeather == WeatherCondition::Storm) {
        bool hasILS = false;
        for (auto& r : RunwayCollection::getAllRunways()) {
            if (r->getStatus() != StatusRunway::RunwayMaintenance && r->hasILS()) {
                hasILS = true;
                break;
            }
        }

        if (!hasILS) {
            std::cout << "No active runways with ILS\n";
            for (auto& f : FlightCatalog::getAllFlights()) {
                if (f->getStatus() == Status::Scheduled) {
                    std::cout << "Flight " << f->getID() << " Storm\n";
                    std::cout << "Refunding passengers for flight ";
                    f->setStatus(Status::Cancelled);
                    try {
                        refund(f->getID());
                    }
                    catch (const std::runtime_error& e) {
                        e.what();
                    }
                }
            }
        }
        notifyObservers();
    }

}
void WeatherDesign::notifyObservers() {
    for (auto& observer : observers) {
        bool found = false;
        for (auto& u : UserColl::getAllUsers()) {
            if (u->getName() == observer) {
                std::cout << " Notification";
                found = true;
            }
        }
        if (!found) {
            std::cout << observer << " not found\n";
        }
    }
}

void WeatherDesign::refund(const std::string& flightId)
{
    for (auto& t : TicketCatalog::getTicketsByFlightId(flightId)) {
        for (auto& u : UserColl::getAllUsers()) {
            if (u->getName() == t->getTicketOwner()) {
                Passenger* p = dynamic_cast<Passenger*>(u.get());
                if (p) {
                    p->addFunds(t->getPaidAmount());
                    std::cout << "Refunded " << t->getTicketOwner() << "\n";
                }
            }
        }
    }
}

const WeatherCondition WeatherDesign::getCurrentCondition() const
{
    return currentCondition;
}
