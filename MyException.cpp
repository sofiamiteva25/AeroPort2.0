#include "MyException.h"

static std::string messageFor(exceptions code)
{
	switch (code) {
	case UnknownPlaneType:                  return "Unknown plane type";
	case CannotCopyThis:                    return "This object cannot be copied";
	case InvalidDataToCreateAirline:        return "Invalid data to create airline";
	case YouDoNotHaveEnoughBalanceToPay:    return "You don't have enough balance to pay";
	case AirlineNotFound:                   return "Airline not found";
	case FlightIsNotScheduled:              return "Flight is not scheduled";
	case ThisPlaneDoesNotHaveFlightAssigned:return "This plane does not have a flight assigned";
	case CannotDelayFlight:                 return "Cannot delay flight";
	case CannotAddFlightWithThisId:         return "Cannot add flight with this id";
	case AlreadyAdded:                      return "Already added";
	case FlightFull:                        return "Flight is full";
	case NoFlightsToDestination:            return "No flights to this destination";
	case NoFlightsInBudget:                 return "No flights in this budget";
	case NoFlightWithThisID:                return "There is no flight with this id";
	case NoFlightWithThisPlaneID:           return "There is no flight with this plane id";
	case FreeRunway:                        return "Runway is free";
	case HangarAlreadyExists:               return "Hangar with this id already exists";
	case PlaneAlreadyInHangar:              return "The plane is already in hangar";
	case CannotAddPlaneInHangar:            return "You cannot add this plane";
	case NoPlaneInHangar:                   return "There is no plane with this id in hangar";
	case HangarNotFound:                    return "Hangar not found";
	case RegisterFirst:                     return "You have to register first";
	case NoTicketFound:                     return "No ticket found for this flight";
	case CannotRefund:                      return "This ticket cannot be refunded";
	case NoEnoghtBalanceForUpgrade:         return "Insufficient balance for upgrade";
	case PlaneHasNoFlightAssigned:          return "This plane does not have a flight assigned";
	case NoPlaneWithId:                     return "Don't have a plane with this id";
	case CannotAddPlane:                    return "Cannot add already added plane";
	case NoAddedPlanes:                     return "No added planes";
	case NoPlaneWithThisFlightId:           return "No plane with this flightId";
	case NotPossibleType:                   return "Not possible type";
	case PlaneNotScheduled:                 return "Plane is not scheduled";
	case RunwayLengthMustBeSet:             return "Runway length must be set before building";
	case RunwayWithIdExists:                return "Runway with this id already exists";
	case NoRunwayWithPlaneId:               return "No runway with this plane id";
	case RunwayWithIdNotFound:              return "Runway with this id not found";
	case RunwayNotFree:                     return "Runway not free";
	case RunwayNotSuitable:                 return "Runway not suitable";
	case invalidName:                       return "Invalid name";
	case NoTicketWithThisOwner:             return "No tickets with this owner";
	case TicketAlreadyAdded:                return "Ticket already added";
	case NoTicketWithThisId:                return "Ticket with this id not found";
	case NotPossibleTicketType:             return "Not available ticket type";
	case PassengerWithThisNameNotFound:     return "Passenger with this name is not found";
	case CannotCreateUser:                  return "Cannot create user";
	case AirlineAlreadyAdded:               return "Airline already added";
	case NotEnoughBalance:                  return "Not enough balance";
	}
	return "Unknown error";
}

static exceptions codeFor(const std::string& msg)
{
	for (int i = 0; i <= static_cast<int>(Unknown); i++) {
		exceptions candidate = static_cast<exceptions>(i);
		if (messageFor(candidate) == msg) {
			return candidate;
		}
	}
	return Unknown;
}

MyException::MyException(const std::string& msg) : message(msg), code(codeFor(msg))
{
}
const char* MyException::what() const noexcept
{
	return message.c_str();
}

exceptions MyException::getCode() const noexcept
{
	return code;
}