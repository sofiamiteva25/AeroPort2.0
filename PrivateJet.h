#pragma once
#include "Plane.h"

class PrivateJet : public Plane {
public:
	PrivateJet(int id, int capacity,
		const std::string& airlineName);
	void setTax()override;
	void changeHealth()override;
	std::unique_ptr<Plane> clone() const override;
	void printInfo(std::ostream& os) const override;
	PrivateJet(const PrivateJet& other);
	void accept(AirportReport& visitor) override;
	void reverseHealth() override;
	void acceptValidator(IRunwayValidatorVisitor& v) const override;
};
