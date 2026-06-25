#pragma once
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class MyException;

enum Status {
	Scheduled,
	Boarding,
	Delayed,
	Departed,
	Cancelled
};
class Flight
{
protected:
	std::string id;
	int planeId;
	std::vector<int> ticketsId;
	std::string destination;
	Status status;
	double ticketAmount;
public:
	Flight(const std::string& id, int planeId,
		const double& ticketAmount, const std::string& destination);
	const std::string getDestination() const;
	const double getTicketPrice() const;
	const std::vector<int>& getTickets() const;
	const Status getStatus() const;
	const std::string getID() const;
	bool canBook() const;
	void addTicket(int ticketId);
	const int getPlaneId() const;
	std::unique_ptr<Flight> clone() const;
	friend std::ostream& operator<<(std::ostream& os, const Flight& flight);
	void setStatus(const Status& newStatus);
	const double getTicketAmount() const;

};
