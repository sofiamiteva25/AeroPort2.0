#pragma once
#include "Plane.h"

class CargoPlane : public Plane {
public:
	CargoPlane(int id,int capacity, 
		const std::string& airlineName);
	void setTax() override;
	void changeHealth() override;
	std::unique_ptr<Plane> clone() const override;
	void printInfo(std::ostream& os) const override;
	CargoPlane(const CargoPlane& other);
	void accept(AirportReport& visitor) override;
	void reverseHealth() override;
	void acceptValidator(IRunwayValidatorVisitor& v) const override;
};
