#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>

class UserColl;

enum WeatherCondition {
	Clear,
	Rain,
	Storm,
	Fog,
	Snow
};

class WeatherDesign
{
	WeatherCondition currentCondition;
	static std::unique_ptr<WeatherDesign> instance;
	std::vector<std::string> observers;

	WeatherDesign();

public:
	static const std::unique_ptr<WeatherDesign>& getInstance();
	void updateWeather(WeatherCondition condition);
	void addObserver(const std::string& observerId);
	void setWeather(WeatherCondition newWeather);
	const WeatherCondition getCurrentCondition() const;
	void notifyObservers();
	void refund(const std::string& flightId);
};
