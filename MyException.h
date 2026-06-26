#pragma once
#include <stdexcept>
#include <string>
enum exceptions {
	UnknownPlaneType,
	CannotCopyThis,
	InvalidDataToCreateAirline,
	YouDoNotHaveEnoughBalanceToPay,
	AirlineNotFound,
	FlightIsNotScheduled,
	ThisPlaneDoesNotHaveFlightAssigned, 
	CannotDelayFlight,
	CannotAddFlightWithThisId,
	AlreadyAdded,
	FlightFull,
	NoFlightsToDestination,
	NoFlightsInBudget,
	NoFlightWithThisID,
	NoFlightWithThisPlaneID,
	FreeRunway,
	HangarAlreadyExists,
	PlaneAlreadyInHangar,
	CannotAddPlaneInHangar,
	NoPlaneInHangar,
	HangarNotFound,
	RegisterFirst,
	NoTicketFound,
	CannotRefund,
	NoEnoghtBalanceForUpgrade,
	PlaneHasNoFlightAssigned,
	NoPlaneWithId,
	CannotAddPlane,
	NoAddedPlanes,
	NoPlaneWithThisFlightId,
	NotPossibleType,
	PlaneNotScheduled,
	RunwayLengthMustBeSet,
	RunwayWithIdExists,
	NoRunwayWithPlaneId,
	RunwayWithIdNotFound,
	RunwayNotFree,
	RunwayNotSuitable,
	invalidName,
	NoTicketWithThisOwner,
	TicketAlreadyAdded,
	NoTicketWithThisId,
	NotPossibleTicketType,
	PassengerWithThisNameNotFound,
	CannotCreateUser,
	AirlineAlreadyAdded,
	NotEnoughBalance,
	Unknown
};


class MyException : public std::exception
{
	std::string message;
	exceptions code;
public:
	MyException(const std::string& s);
	const char* what() const noexcept override;
	exceptions getCode() const noexcept;
};