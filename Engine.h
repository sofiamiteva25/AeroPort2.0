#pragma once
#include "Administrator.h"
#include "LogInterface.h"
#include "TraficControl.h"
#include "ProjectSerializer.h"
#include "WeatherDesign.h"
#include "UserFactory.h"
#include "UserColl.h"
#include "MyException.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Engine
{
	static Engine* engine;
	Engine();
	std::unique_ptr<LogInterface> logI;

public:
	static Engine* getEngine();
	void command(std::string msg);
	std::string acceptComand();
	void handleAdmin(std::string msg);
	void handlePassenger(std::string msg);
	void handleTrafficControl(std::string msg);
	void handleLog(std::string msg);
	void handleSerializer(std::string msg);
	~Engine() = default;


};

