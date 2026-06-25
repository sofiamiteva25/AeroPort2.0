#pragma once
// Original Person.h declared Passenger, Administrator, UserColl, and UserFactory
// together in one file. Each class now lives in its own header; this aggregator
// is kept so existing #include "Person.h" usages keep compiling unchanged.
#include "Passenger.h"
#include "Administrator.h"
#include "UserColl.h"
#include "UserFactory.h"

//class PassengerColl {
//	static std::vector<std::unique_ptr<Passenger>> passengers;
//public:
//	static const std::vector<std::unique_ptr<Passenger>>& getAllPassengers();
//	static const std::unique_ptr<Passenger>& getPassengerByName(std::string name);
//	static void addUser(std::unique_ptr<Passenger> p);
//};
